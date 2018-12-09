#include <iostream>
#include <random>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

struct Cricket {
    int stamina;           // 耐力
    int pugnacity;         // 斗性
    int momentum;          // 气势
    int wrestle;           // 角力
    int jaw;               // 牙钳
    int critRate;          // 暴击率
    int critDamageInc;     // 暴击伤害增加
    int blockRate;         // 防御率
    int blockDamageDec;    // 防御伤害减少
    int counterRate;       // 反击率
    std::string name = ""; // 促织名称
    int durability = 100;  // 耐久
    int attackDurabilityRate = 0; // 此值与暴击率相加代表暴击后减耐久的概率
};

// 是否发生一个概率为rate%的事件
bool roll(int rate)
{
    static std::random_device rd;  
    static std::mt19937 gen(rd()); 
    static std::uniform_int_distribution dis(0, 99);
    if (dis(gen) < rate) return true;
    else return false;
}

enum Winner {left, right, unknown};

// c0攻击c1，不包含反击
Winner singleAttack(Cricket &c0, Cricket &c1, bool isFirst = false, bool isCounter = false)
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
bool fight(Cricket c0, Cricket c1)
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

Cricket crickets[] = {
    {40, 50, 1, 1, 1, 60, 35, 0, 0, 60, "xiuhuazhen", 11, -10},
    {110, 110, 7, 13, 7, 20, 8, 0, 0, 80, "liangtouqiang", 14, 15},
    {80, 70, 22, 5, 6, 40, 5, 0, 0, 40, "chuiling", 13, 0},
    {140, 150, 4, 7, 4, 55, 5, 55, 10, 100, "paomahuang", 16, -5},
    {120, 120, 9, 12, 13, 25, 10, 30, 8, 35, "yuchutou", 15, 10},
    {280, 200, 6, 6, 6, 0, 0, 80, 5, 50, "pipaoxuanjia", 23, 20},
    {90, 90, 7, 11, 9, 65, 12, 0, 0, 75, "fanshengming", 13, -15},
    {140, 100, 8, 9, 13, 30, 18, 30, 8, 30, "zhushae", 16, 0},
    {180, 160, 6, 16, 10, 20, 10, 45, 18, 35, "toutuo", 18, 10},
    {170, 170, 5, 24, 8, 0, 0, 35, 10, 55, "tiedanzi", 17, 30},
    {190, 130, 8, 10, 10, 35, 18, 30, 8, 40, "chixu", 18, 5},
    {90, 90, 4, 3, 24, 40, 24, 0, 0, 30, "yuwei", 13, 0},
    {180, 120, 8, 15, 15, 25, 8, 60, 8, 55, "youzhideng", 18, 10},
    {220, 180, 13, 10, 12, 20, 10, 45, 10, 30, "zhensanse", 20, 0},
    {150, 200, 10, 9, 11, 45, 14, 25, 15, 45, "caosanduan", 16, 0},
    {160, 190, 11, 12, 10, 25, 20, 20, 20, 35, "zhenzihuang", 17, 20},
    {90, 140, 24, 1, 14, 70, 10, 0, 0, 70, "meihuachi", 13, -20},
    {290, 290, 12, 11, 13, 35, 15, 35, 15, 35, "tianlanqing", 23, 0},
    {150, 150, 20, 20, 20, 50, 20, 30, 10, 40, "sanduanjin", 16, 0},
    {80, 460, 8, 7, 9, 75, 1, 75, 50, 75, "santaizi", 13, 15},
    {180, 800, 1, 1, 1, 95, 1, 95, 25, 800, "babai", 18, -55},
    {200, 150, 9, 10, 11, 15, 5, 35, 10, 50, "zhenqing", 18, 15},
    {150, 200, 8, 12, 9, 25, 8, 30, 12, 30, "zhenhuang", 15, 10},
    {140, 140, 10, 7, 10, 35, 10, 25, 15, 35, "zhenzi", 15, 5},
    {100, 100, 5, 5, 14, 50, 14, 0, 0, 40, "zhenhong", 13, -5},
    {130, 90, 6, 14, 8, 20, 5, 50, 8, 65, "zhenwu", 14, 5},
    {90, 130, 14, 3, 7, 45, 12, 0, 0, 45, "zhenbai", 12, -10},
    {160, 100, 14, 6, 6, 7, 6, 65, 15, 10, "zhongqingjinsuoyi", 15, 10},
    {160, 100, 17, 6, 6, 7, 6, 60, 13, 10, "zhongqingliuyifei", 15, 10},
    {150, 120, 15, 6, 7, 9, 6, 60, 14, 10, "shaqingjinsuoyi", 14, 10},
    {150, 120, 18, 6, 7, 9, 6, 55, 12, 10, "shaqingliuyifei", 14, 10}
};
        
int main()
{
    int N = 10000;
    int numCrickets = std::size(crickets);
    std::vector<std::vector<double>> res(numCrickets);
    for (int i = 0; i != numCrickets; ++i) {
        for (int j = 0; j != i; ++j)
            std::cout << 1 - res[j][i - j - 1] << '\t';
        std::cout << '\t';
        for (int j = i + 1; j != numCrickets; ++j) {
            int counter = 0;
            for (int k = 0; k != N; ++k) if (fight(crickets[i], crickets[j])) ++counter;
            auto winFrequency = static_cast<double>(counter) / N;
            res[i].emplace_back(winFrequency);
            std::cout << winFrequency << '\t';
        }
        std::cout << '\n';
    }
}
