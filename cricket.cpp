#include <iostream>
#include <random>
#include <tuple>
#include "cricket.h"

namespace cricketNs {

// 是否发生一个概率为rate%的事件
bool roll(int rate)
{
    static std::random_device rd;  
    static std::mt19937 gen(rd()); 
    static std::uniform_int_distribution dis(0, 99);
    if (dis(gen) < rate) return true;
    else return false;
}

// c0攻击c1，不包含反击
Winner singleAttack(Cricket &c0, Cricket &c1, bool isFirst, bool isCounter)
{
    auto jawDamage = (isCounter ? c0.wrestle : c0.jaw); 
    auto momentumDamage = c0.momentum;
    auto isCrit = roll(c0.critRate);
    if (isCrit) jawDamage += c0.critDamageInc; // 暴击
    else if (isFirst) momentumDamage = 0; // 第一次攻击如果不是暴击不减斗性
    if (roll(c1.blockRate)) { // 被防御
        jawDamage -= c1.blockDamageDec;
        momentumDamage -= c1.blockDamageDec;
    }
    else if (isCrit && roll(c0.critRate + c0.attackDurabilityRate)) { // 减耐久
        //std::cout << c1.name << " durability -1" << '\n';
        if (--c1.durability <= 0) return Winner::left;
    }
    
    if (jawDamage < 0) jawDamage = 0;
    if (momentumDamage < 0) momentumDamage = 0;
    //std::cout << c1.name << ' ' << jawDamage << ' ' << momentumDamage << '\n';
    c1.stamina -= jawDamage;
    if (c1.stamina <= 0) return Winner::left;
    c1.pugnacity -= momentumDamage;
    if (c1.pugnacity <= 0) return Winner::left;
    return Winner::unknown;
}

// c0攻击c1，包含反击，返回的bool指示是否发生了反击（以供之后判断是否追击）
std::pair<Winner, bool> attack(Cricket &c0, Cricket &c1)
{
    if (singleAttack(c0, c1, true) == Winner::left) return {Winner::left, false};
    if (!roll(c1.counterRate)) return {Winner::unknown, false}; // 没有发生反击
    auto c0counterRate = c0.counterRate;
    auto c1counterRate = c1.counterRate;
    do {
        c0counterRate -= 5; // 每次反击后反击率-5
        c1counterRate -= 5;
        if (singleAttack(c1, c0, false, true) == Winner::left) return {Winner::right, true};
        if (roll(c0counterRate)) {
            c0counterRate -= 5;
            c1counterRate -= 5;
            if (singleAttack(c0, c1) == Winner::left) return {Winner::left, true};
        }
        else return {Winner::unknown, true};
    } while (roll(c1counterRate));
    return {Winner::unknown, true};
}

// c0与c1战斗，如果c0赢返回true，否则false
bool fight(Cricket &c0, Cricket &c1)
{
    bool c0offensive; 
    Cricket *pOffensive, *pDefensive;
    for (;;) {
        // 气势攻击
        if (c0.momentum > c1.momentum) {
            c1.pugnacity -= c0.momentum;
            //std::cout << '\n' << c1.name << ' ' << 0 << ' ' << c0.momentum << '\n';
            if (c1.pugnacity < 0) return true;
            c0offensive = roll(80); // 接下来c0有80%的概率先手攻击
        }
        else if (c0.momentum < c1.momentum) {
            c0.pugnacity -= c1.momentum;
            //std::cout << '\n' << c0.name << ' ' << 0 << ' ' << c1.momentum << '\n';
            if (c0.pugnacity < 0) return false;
            c0offensive = roll(20); // 接下来c0有20%的概率先手攻击
        }
        else c0offensive = roll(50); // 接下来c0有50%的概率先手攻击
        
        // pOffensive指向先手攻击者，pDefensive指向后手攻击者
        if (c0offensive) {
            pOffensive = &c0;
            pDefensive = &c1;
        }
        else {
            pOffensive = &c1;
            pDefensive = &c0;
        }
        
        auto [winner, hasCounter] = attack(*pOffensive, *pDefensive);
        if (winner == Winner::left) return c0offensive;
        else if (winner == Winner::right) return !c0offensive;
        do {
            std::tie(winner, hasCounter) = attack(*pDefensive, *pOffensive);
            if (winner == Winner::left) return !c0offensive;
            else if (winner == Winner::right) return c0offensive;
            if (hasCounter) { // 如果发生了反击，进行追击
                std::tie(winner, hasCounter) = attack(*pOffensive, *pDefensive);
                if (winner == Winner::left) return c0offensive;
                else if (winner == Winner::right) return !c0offensive;
            }
        } while (hasCounter);
    }
}

// 计算c0对c1的胜率，比赛n场
double winRate(const Cricket &c0, const Cricket &c1, int n)
{
    int counter = 0;
    for (int i = 0; i != n; ++i) {
        auto c0tmp = c0, c1tmp = c1;
        if (fight(c0tmp, c1tmp)) ++counter;
    }
    return static_cast<double>(counter) / n;
}

}
