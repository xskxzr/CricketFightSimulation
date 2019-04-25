#ifndef CRICKET_H
#define CRICKET_H

#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>

namespace cricketNs {

struct CricketBase {
    int stamina;              // 耐力
    int pugnacity;            // 斗性
    int momentum;             // 气势
    int wrestle;              // 角力
    int jaw;                  // 牙钳
    int critRate;             // 暴击率
    int critDamageInc;        // 暴击伤害增加
    int attackDurabilityRate; // 此值与暴击率相加代表暴击后减耐久的概率
    int blockRate;            // 防御率
    int blockDamageDec;       // 防御伤害减少
    int counterRate;          // 反击率
    std::string name = "";    // 促织名称
    int durability = 100;     // 耐久
};

struct Cricket : public CricketBase {
    Cricket(const CricketBase &base) : CricketBase{base} {}
    
    Cricket(int stamina,              
            int pugnacity,        
            int momentum,           
            int wrestle,             
            int jaw,                 
            int critRate,           
            int critDamageInc,      
            int attackDurabilityRate, 
            int blockRate,          
            int blockDamageDec,      
            int counterRate,          
            std::string_view name = "",    
            int durability = 100) :
        CricketBase {
            stamina,
            pugnacity,
            momentum,
            wrestle,
            jaw,
            critRate,
            critDamageInc,
            attackDurabilityRate,
            blockRate,
            blockDamageDec, 
            counterRate,
            {name.begin(), name.end()},
            durability
        } {}
        
    // 从名字构造一、二品促织王
    Cricket(std::string_view name) : CricketBase{kings.find({name.begin(), name.end()})->second} {}
    
    Cricket(std::string_view name, int durability) : CricketBase{kings.find({name.begin(), name.end()})->second} {
        this->durability = durability;
    }
    
    // 从名字构造其他促织
    Cricket(std::string_view name0, std::string_view name1, int durability = 100) {
        auto &affix0 = affixes.find({name0.begin(), name0.end()})->second;
        auto &affix1 = affixes.find({name1.begin(), name1.end()})->second;
        this->stamina = affix0.stamina + affix1.stamina;
        this->pugnacity = affix0.pugnacity + affix1.pugnacity;
        this->momentum = affix0.momentum + affix1.momentum;
        this->wrestle = affix0.wrestle + affix1.wrestle;
        this->jaw = affix0.jaw + affix1.jaw;
        this->critRate = affix0.critRate + affix1.critRate;
        this->critDamageInc = affix0.critDamageInc + affix1.critDamageInc;
        this->attackDurabilityRate = affix0.attackDurabilityRate + affix1.attackDurabilityRate;
        this->blockRate = affix0.blockRate + affix1.blockRate;
        this->blockDamageDec = affix0.blockDamageDec + affix1.blockDamageDec;
        this->counterRate = affix0.counterRate + affix1.counterRate;
        this->name = name0;
        this->name += name1;
        this->durability = durability;
    }
        
    static inline const std::unordered_map<std::string, CricketBase> kings {
        {"xiuhuazhen",    {40,  50,  1,  1,  1,  60, 35, -10, 0,  0,  60,  "xiuhuazhen", 11}},
        {"liangtouqiang", {110, 110, 7,  13, 7,  20, 8,  15,  0,  0,  80,  "liangtouqiang", 14}},
        {"chuiling",      {80,  70,  22, 5,  6,  40, 5,  0,   0,  0,  40,  "chuiling", 13}},
        {"paomahuang",    {140, 150, 4,  7,  4,  55, 5,  -5,  55, 10, 100, "paomahuang", 16}},
        {"yuchutou",      {120, 120, 9,  12, 13, 25, 10, 10,  30, 8,  35,  "yuchutou", 15}},
        {"pipaoxuanjia",  {280, 200, 6,  6,  6,  0,  0,  20,  80, 5,  50,  "pipaoxuanjia", 23}},
        {"fanshengming",  {90,  90,  7,  11, 9,  65, 12, -15, 0,  0,  75,  "fanshengming", 13}},
        {"zhushae",       {140, 100, 8,  9,  13, 30, 18, 0,   30, 8,  30,  "zhushae", 16}},
        {"toutuo",        {180, 160, 6,  16, 10, 20, 10, 10,  45, 18, 35,  "toutuo", 18}},
        {"tiedanzi",      {170, 170, 5,  24, 8,  0,  0,  30,  35, 10, 55,  "tiedanzi", 17}},
        {"chixu",         {190, 130, 8,  10, 10, 35, 18, 5,   30, 8,  40,  "chixu", 18}},
        {"yuwei",         {90,  90,  4,  3,  24, 40, 24, 0,   0,  0,  30,  "yuwei", 13}},
        {"youzhideng",    {180, 120, 8,  15, 15, 25, 8,  10,  60, 8,  55,  "youzhideng", 18}},
        {"zhensanse",     {220, 180, 13, 10, 12, 20, 10, 0,   45, 10, 30,  "zhensanse", 20}},
        {"caosanduan",    {150, 200, 10, 9,  11, 45, 14, 0,   25, 15, 45,  "caosanduan", 16}},
        {"zhenzihuang",   {160, 190, 11, 12, 10, 25, 20, 20,  20, 20, 35,  "zhenzihuang", 17}},
        {"meihuachi",     {90,  140, 24, 1,  14, 70, 10, -20, 0,  0,  70,  "meihuachi", 13}},
        {"tianlanqing",   {290, 290, 12, 11, 13, 35, 15, 0,   35, 15, 35,  "tianlanqing", 23}},
        {"sanduanjin",    {150, 150, 20, 20, 20, 50, 20, 0,   30, 10, 40,  "sanduanjin", 16}},
        {"santaizi",      {80,  460, 8,  7,  9,  75, 1,  15,  75, 50, 75,  "santaizi", 13}},
        {"babai",         {180, 800, 1,  1,  1,  95, 1,  -55, 95, 25, 800, "babai", 18}},
        {"zhenqing",      {200, 150, 9,  10, 11, 15, 5,  15,  35, 10, 50,  "zhenqing", 18}},
        {"zhenhuang",     {150, 200, 8,  12, 9,  25, 8,  10,  30, 12, 30,  "zhenhuang", 15}},
        {"zhenzi",        {140, 140, 10, 7,  10, 35, 10, 5,   25, 15, 35,  "zhenzi", 15}},
        {"zhenhong",      {100, 100, 5,  5,  14, 50, 14, -5,  0,  0,  40,  "zhenhong", 13}},
        {"zhenwu",        {130, 90,  6,  14, 8,  20, 5,  5,   50, 8,  65,  "zhenwu", 14}},
        {"zhenbai",       {90,  130, 14, 3,  7,  45, 12, -10, 0,  0,  45,  "zhenbai", 12}}
    };
    
    static inline const std::unordered_map<std::string, CricketBase> affixes {
        {"zhengqing",    {150, 80,  2,  3,  4,  5,  5, 10,  25, 5,  10}},
        {"qing",         {150, 80,  2,  3,  4,  5,  5, 10,  25, 5,  10}},
        {"danqing",      {130, 100, 3,  4,  5,  8,  4, 10,  25, 4,  15}},
        {"baiqing",      {140, 90,  5,  4,  5,  7,  4, 10,  20, 5,  15}},
        {"xieqing",      {150, 80,  5,  6,  6,  6,  5, 10,  25, 7,  15}},
        {"xiekeqing",    {150, 80,  5,  6,  6,  6,  5, 10,  25, 7,  15}},
        {"zhongqing",    {160, 100, 5,  6,  6,  7,  6, 10,  25, 8,  10}},
        {"shaqing",      {150, 120, 6,  6,  7,  9,  6, 10,  20, 7,  15}},
        {"hongshaqing",  {150, 120, 6,  6,  7,  9,  6, 10,  20, 7,  15}},
        {"zhenghuang",   {100, 160, 1,  4,  2,  15, 5, 0,   15, 5,  20}},
        {"huang",        {100, 160, 1,  4,  2,  15, 5, 0,   15, 5,  20}},
        {"danhuang",     {90,  120, 3,  7,  3,  18, 7, 0,   10, 6,  25}},
        {"anhuang",      {100, 140, 2,  6,  5,  10, 6, 0,   15, 8,  25}},
        {"baihuang",     {90,  160, 4,  7,  5,  15, 5, 0,   10, 6,  20}},
        {"heihuang",     {110, 160, 3,  8,  6,  15, 6, 0,   18, 7,  20}},
        {"youhuang",     {120, 170, 4,  9,  5,  18, 7, 0,   15, 7,  25}},
        {"zhengzi",      {70,  70,  4,  2,  3,  25, 6, -10, 10, 8,  30}},
        {"zi",           {70,  70,  4,  2,  3,  25, 6, -10, 10, 8,  30}},
        {"danzi",        {60,  70,  4,  2,  4,  30, 7, -10, 10, 7,  30}},
        {"lizi",         {80,  80,  5,  2,  5,  20, 5, -10, 15, 10, 25}},
        {"lizizi",       {80,  80,  5,  2,  5,  20, 5, -10, 15, 10, 25}},
        {"heizi",        {90,  80,  5,  3,  5,  25, 6, -10, 12, 12, 25}},
        {"shazi",        {70,  70,  6,  4,  6,  30, 8, -10, 15, 10, 30}},
        {"hongshazi",    {70,  70,  6,  4,  6,  30, 8, -10, 15, 10, 30}},
        {"baizi",        {80,  80,  7,  5,  6,  30, 7, -10, 12, 12, 30}},
        {"zhenghong",    {50,  50,  2,  2,  5,  30, 7, -10, 0,  0,  30}},
        {"hong",         {50,  50,  2,  2,  5,  30, 7, -10, 0,  0,  30}},
        {"baihong",      {50,  60,  3,  3,  5,  35, 7, -10, 0,  0,  25}},
        {"zihong",       {60,  60,  2,  4,  6,  35, 9, -10, 0,  0,  30}},
        {"jinhong",      {70,  60,  4,  5,  7,  30, 7, -10, 0,  0,  25}},
        {"xiahong",      {60,  50,  5,  4,  8,  30, 9, -10, 0,  0,  30}},
        {"luoxiahong",   {60,  50,  5,  4,  8,  30, 9, -10, 0,  0,  30}},
        {"xuehong",      {60,  70,  4,  4,  9,  40, 9, -10, 0,  0,  30}},
        {"shiliuhong",   {60,  70,  4,  4,  9,  40, 9, -10, 0,  0,  30}},
        {"zhenghei",     {70,  60,  1,  4,  1,  10, 3, 5,   20, 5,  45}},
        {"hei",          {70,  60,  1,  4,  1,  10, 3, 5,   20, 5,  45}},
        {"huihei",       {60,  40,  2,  5,  2,  8,  3, 5,   25, 6,  50}},
        {"mahei",        {80,  60,  1,  6,  2,  10, 4, 5,   25, 7,  45}},
        {"mohei",        {90,  50,  2,  7,  4,  8,  4, 5,   20, 6,  45}},
        {"zaohei",       {90,  70,  1,  8,  4,  10, 4, 5,   25, 8,  50}},
        {"guozaohei",    {90,  70,  1,  8,  4,  10, 4, 5,   25, 8,  50}},
        {"tanhei",       {80,  70,  2,  9,  4,  12, 4, 5,   30, 10, 50}},
        {"zhengbai",     {40,  30,  3,  1,  2,  30, 5, -10, 0,  0,  30}},
        {"bai",          {40,  30,  3,  1,  2,  30, 5, -10, 0,  0,  30}},
        {"yabai",        {50,  40,  4,  2,  2,  25, 6, -10, 0,  0,  25}},
        {"danbai",       {40,  50,  5,  2,  2,  30, 6, -10, 0,  0,  35}},
        {"huabai",       {50,  40,  6,  1,  3,  30, 7, -10, 0,  0,  30}},
        {"luhuabai",     {50,  40,  6,  1,  3,  30, 7, -10, 0,  0,  30}},
        {"yuebai",       {40,  50,  8,  2,  2,  35, 7, -10, 0,  0,  35}},
        {"yubai",        {50,  40,  9,  2,  4,  30, 8, -10, 0,  0,  30}},
        {"shitou",       {10,  10,  0,  1,  0,  0,  0, 0,   0,  0,  5}},
        {"qiantou",      {10,  10,  0,  1,  0,  0,  0, 0,   0,  0,  7}},
        {"yuantou",      {10,  10,  0,  1,  0,  0,  0, 0,   0,  0,  9}},
        {"jiantou",      {20,  10,  0,  2,  0,  0,  0, 0,   0,  0,  11}},
        {"fangtou",      {20,  10,  0,  2,  0,  0,  0, 0,   0,  0,  13}},
        {"datou",        {20,  10,  0,  2,  0,  0,  0, 0,   0,  0,  15}},
        {"matou",        {20,  20,  0,  3,  0,  0,  0, 0,   0,  0,  17}},
        {"heilian",      {20,  20,  0,  3,  0,  0,  0, 0,   0,  0,  19}},
        {"honge",        {20,  20,  0,  3,  0,  0,  0, 0,   0,  0,  21}},
        {"jinding",      {30,  20,  0,  4,  0,  0,  0, 0,   0,  0,  23}},
        {"sanjiantou",   {30,  20,  0,  4,  0,  0,  0, 0,   0,  0,  25}},
        {"baoshitou",    {30,  20,  0,  4,  0,  0,  0, 0,   0,  0,  27}},
        {"hupotou",      {30,  30,  0,  5,  0,  0,  0, 0,   0,  0,  30}},
        {"hudietou",     {30,  30,  0,  5,  0,  0,  0, 0,   0,  0,  32}},
        {"yuding",       {40,  40,  0,  6,  0,  0,  0, 0,   0,  0,  34}},
        {"qingtingtou",  {40,  40,  0,  7,  0,  0,  0, 0,   0,  0,  36}},
        {"putitou",      {50,  50,  0,  8,  0,  0,  0, 0,   0,  0,  38}},
        {"shouxingtou",  {50,  50,  0,  9,  0,  0,  0, 0,   0,  0,  40}},
        {"yuanchi",      {0,   0,   1,  0,  0,  0,  0, 0,   5,  1,  0}},
        {"fangchi",      {0,   0,   1,  0,  0,  0,  0, 0,   7,  1,  0}},
        {"jianchi",      {0,   0,   1,  0,  0,  0,  0, 0,   9,  1,  0}},
        {"kuochi",       {0,   0,   2,  0,  0,  0,  0, 0,   11, 2,  0}},
        {"wubei",        {0,   0,   2,  0,  0,  0,  0, 0,   13, 2,  0}},
        {"qiaochi",      {0,   0,   2,  0,  0,  0,  0, 0,   15, 2,  0}},
        {"yinyangchi",   {0,   0,   3,  0,  0,  0,  0, 0,   17, 3,  0}},
        {"lanyi",        {0,   0,   3,  0,  0,  0,  0, 0,   19, 3,  0}},
        {"changyi",      {0,   0,   3,  0,  0,  0,  0, 0,   21, 3,  0}},
        {"zichi",        {0,   0,   4,  0,  0,  0,  0, 0,   23, 4,  0}},
        {"yinbei",       {0,   0,   4,  0,  0,  0,  0, 0,   25, 4,  0}},
        {"feichi",       {0,   0,   4,  0,  0,  0,  0, 0,   27, 4,  0}},
        {"bolichi",      {0,   0,   5,  0,  0,  0,  0, 0,   30, 5,  0}},
        {"wujinchi",     {0,   0,   5,  0,  0,  0,  0, 0,   32, 5,  0}},
        {"qingjinchi",   {0,   0,   6,  0,  0,  0,  0, 0,   34, 6,  0}},
        {"pipachi",      {0,   0,   7,  0,  0,  0,  0, 0,   36, 6,  0}},
        {"ziwuda",       {0,   0,   8,  0,  0,  0,  0, 0,   38, 7,  0}},
        {"jinsuoyi",     {0,   0,   9,  0,  0,  0,  0, 0,   40, 7,  0}},
        {"shuiya",       {0,   0,   0,  0,  1,  5,  1, -3,  0,  0,  0}},
        {"huaya",        {0,   0,   0,  0,  1,  7,  1, -4,  0,  0,  0}},
        {"huangya",      {0,   0,   0,  0,  1,  9,  1, -5,  0,  0,  0}},
        {"ziya",         {0,   0,   0,  0,  2,  11, 2, -6,  0,  0,  0}},
        {"baiya",        {0,   0,   0,  0,  2,  13, 2, -7,  0,  0,  0}},
        {"hongya",       {0,   0,   0,  0,  2,  15, 2, -8,  0,  0,  0}},
        {"zhimaya",      {0,   0,   0,  0,  3,  17, 3, -9,  0,  0,  0}},
        {"zihuaqian",    {0,   0,   0,  0,  3,  19, 3, -10, 0,  0,  0}},
        {"zhiya",        {0,   0,   0,  0,  3,  21, 3, -11, 0,  0,  0}},
        {"zhadaoya",     {0,   0,   0,  0,  4,  23, 4, -12, 0,  0,  0}},
        {"huadanya",     {0,   0,   0,  0,  4,  25, 4, -13, 0,  0,  0}},
        {"yuanyangya",   {0,   0,   0,  0,  4,  27, 4, -14, 0,  0,  0}},
        {"heihongqian",  {0,   0,   0,  0,  5,  30, 5, -15, 0,  0,  0}},
        {"hongzhuqian",  {0,   0,   0,  0,  5,  32, 5, -16, 0,  0,  0}},
        {"zhudingqian",  {0,   0,   0,  0,  6,  34, 6, -17, 0,  0,  0}},
        {"baiguya",      {0,   0,   0,  0,  7,  36, 6, -18, 0,  0,  0}},
        {"tiemenshuan",  {0,   0,   0,  0,  8,  38, 7, -19, 0,  0,  0}},
        {"wugangqian",   {0,   0,   0,  0,  9,  40, 7, -20, 0,  0,  0}},
        {"heiyan",       {0,   0,   0,  0,  0,  15, 3, -5,  15, 3,  15}},
        {"riyueyan",     {0,   0,   0,  0,  0,  20, 4, -5,  20, 4,  20}},
        {"yinyangyan",   {0,   0,   0,  0,  0,  25, 5, -5,  25, 5,  25}},
        {"sanxian",      {10,  10,  2,  2,  2,  0,  0, 0,   0,  0,  0}},
        {"yixian",       {20,  20,  3,  3,  3,  0,  0, 0,   0,  0,  0}},
        {"baxian",       {30,  30,  4,  4,  4,  0,  0, 0,   0,  0,  0}},
        {"guijia",       {50,  0,   0,  0,  0,  0,  0, 0,   30, 4,  0}},
        {"jinshudai",    {60,  0,   0,  0,  0,  0,  0, 0,   35, 5,  0}},
        {"longlinjia",   {70,  0,   0,  0,  0,  0,  0, 0,   40, 6,  0}},
        {"yuangyangxu",  {0,   50,  0,  0,  0,  30, 4, -20, 0,  0,  0}},
        {"zhujiexu",     {0,   60,  0,  0,  0,  35, 5, -20, 0,  0,  0}},
        {"hudiexu",      {0,   70,  0,  0,  0,  40, 6, -20, 0,  0,  0}},
        {"tiexiang",     {0,   0,   0,  0,  0,  0,  0, 0,   35, 7,  0}},
        {"xuehua",       {0,   0,   0,  0,  0,  0,  0, 0,   40, 8,  0}},
        {"lanban",       {0,   0,   0,  0,  0,  0,  0, 0,   45, 9,  0}},
        {"sanchajiang",  {0,   0,   0,  7,  0,  0,  0, 0,   0,  0,  35}},
        {"xianchuantui", {0,   0,   0,  8,  0,  0,  0, 0,   0,  0,  40}},
        {"bazhu",        {0,   0,   0,  9,  0,  0,  0, 0,   0,  0,  45}},
        {"sheban",       {0,   0,   0,  0,  0,  35, 7, -25, 0,  0,  0}},
        {"honglingmen",  {0,   0,   0,  0,  0,  40, 8, -25, 0,  0,  0}},
        {"honghaier",    {0,   0,   0,  0,  0,  45, 9, -25, 0,  0,  0}},
        {"suodu",        {50,  50,  0,  0,  0,  0,  0, 0,   0,  0,  0}},
        {"zaohe",        {70,  70,  0,  0,  0,  0,  0, 0,   0,  0,  0}},
        {"bake",         {90,  90,  0,  0,  0,  0,  0, 0,   0,  0,  0}},
        {"liuyifei",     {0,   0,   12, 0,  0,  0,  0, 0,   35, 5,  0}},
        {"chizhao",      {40,  40,  0,  12, 0,  0,  0, 0,   0,  0,  35}},
        {"dachongya",    {0,   0,   0,  0,  12, 35, 5, -15, 0,  0,  0}}
    };
};

enum Winner {left, right, unknown};

// c0攻击c1，不包含反击
Winner singleAttack(Cricket &c0, Cricket &c1, bool isFirst = false, bool isCounter = false);

// c0攻击c1,包含反击，返回的bool指示是否发生了反击（以供之后判断是否追击）
std::pair<Winner, bool> attack(Cricket &c0, Cricket &c1);

// c0与c1战斗，如果c0赢返回true,否则false
bool fight(Cricket &c0, Cricket &c1);

// 计算c0对c1的胜率,比赛n场
double winRate(const Cricket &c0, const Cricket &c1, int n = 10000);

}

#endif
