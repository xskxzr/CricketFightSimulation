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
    
    Cricket(const CricketBase &affix0, const CricketBase &affix1, int durability = 100) :
        CricketBase {
            affix0.stamina + affix1.stamina,
            affix0.pugnacity + affix1.pugnacity,
            affix0.momentum + affix1.momentum,
            affix0.wrestle + affix1.wrestle,
            affix0.jaw + affix1.jaw,
            affix0.critRate + affix1.critRate,
            affix0.critDamageInc + affix1.critDamageInc,
            affix0.attackDurabilityRate + affix1.attackDurabilityRate,
            affix0.blockRate + affix1.blockRate,
            affix0.blockDamageDec + affix1.blockDamageDec, 
            affix0.counterRate + affix1.counterRate,
            affix0.name + affix1.name,
            durability
        } {}
    
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
    Cricket(std::string_view name) : Cricket{kings.find({name.begin(), name.end()})->second} {}
    
    Cricket(std::string_view name, int durability) : Cricket{kings.find({name.begin(), name.end()})->second} 
    {
        this->durability = durability;
    }
    
    // 从名字构造其他促织
    Cricket(std::string_view name0, std::string_view name1, int durability = 100) :
        Cricket {
            affixes.find({name0.begin(), name0.end()})->second, 
            affixes.find({name1.begin(), name1.end()})->second,
            durability
        } {}
        
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
        {"zhengqing",    {150, 80,  2,  3,  4,  5,  5, 10,  25, 5,  10, "zhengqing"}},
        {"qing",         {150, 80,  2,  3,  4,  5,  5, 10,  25, 5,  10, "qing"}},
        {"danqing",      {130, 100, 3,  4,  5,  8,  4, 10,  25, 4,  15, "danqing"}},
        {"baiqing",      {140, 90,  5,  4,  5,  7,  4, 10,  20, 5,  15, "baiqing"}},
        {"xieqing",      {150, 80,  5,  6,  6,  6,  5, 10,  25, 7,  15, "xieqing"}},
        {"xiekeqing",    {150, 80,  5,  6,  6,  6,  5, 10,  25, 7,  15, "xiekeqing"}},
        {"zhongqing",    {160, 100, 5,  6,  6,  7,  6, 10,  25, 8,  10, "zhongqing"}},
        {"shaqing",      {150, 120, 6,  6,  7,  9,  6, 10,  20, 7,  15, "shaqing"}},
        {"hongshaqing",  {150, 120, 6,  6,  7,  9,  6, 10,  20, 7,  15, "hongshaqing"}},
        {"zhenghuang",   {100, 160, 1,  4,  2,  15, 5, 0,   15, 5,  20, "zhenghuang"}},
        {"huang",        {100, 160, 1,  4,  2,  15, 5, 0,   15, 5,  20, "huang"}},
        {"danhuang",     {90,  120, 3,  7,  3,  18, 7, 0,   10, 6,  25, "danhuang"}},
        {"anhuang",      {100, 140, 2,  6,  5,  10, 6, 0,   15, 8,  25, "anhuang"}},
        {"baihuang",     {90,  160, 4,  7,  5,  15, 5, 0,   10, 6,  20, "baihuang"}},
        {"heihuang",     {110, 160, 3,  8,  6,  15, 6, 0,   18, 7,  20, "heihuang"}},
        {"youhuang",     {120, 170, 4,  9,  5,  18, 7, 0,   15, 7,  25, "youhuang"}},
        {"zhengzi",      {70,  70,  4,  2,  3,  25, 6, -10, 10, 8,  30, "zhengzi"}},
        {"zi",           {70,  70,  4,  2,  3,  25, 6, -10, 10, 8,  30, "zi"}},
        {"danzi",        {60,  70,  4,  2,  4,  30, 7, -10, 10, 7,  30, "danzi"}},
        {"lizi",         {80,  80,  5,  2,  5,  20, 5, -10, 15, 10, 25, "lizi"}},
        {"lizizi",       {80,  80,  5,  2,  5,  20, 5, -10, 15, 10, 25, "lizizi"}},
        {"heizi",        {90,  80,  5,  3,  5,  25, 6, -10, 12, 12, 25, "heizi"}},
        {"shazi",        {70,  70,  6,  4,  6,  30, 8, -10, 15, 10, 30, "shazi"}},
        {"hongshazi",    {70,  70,  6,  4,  6,  30, 8, -10, 15, 10, 30, "hongshazi"}},
        {"baizi",        {80,  80,  7,  5,  6,  30, 7, -10, 12, 12, 30, "baizi"}},
        {"zhenghong",    {50,  50,  2,  2,  5,  30, 7, -10, 0,  0,  30, "zhenghong"}},
        {"hong",         {50,  50,  2,  2,  5,  30, 7, -10, 0,  0,  30, "hong"}},
        {"baihong",      {50,  60,  3,  3,  5,  35, 7, -10, 0,  0,  25, "baihong"}},
        {"zihong",       {60,  60,  2,  4,  6,  35, 9, -10, 0,  0,  30, "zihong"}},
        {"jinhong",      {70,  60,  4,  5,  7,  30, 7, -10, 0,  0,  25, "jinhong"}},
        {"xiahong",      {60,  50,  5,  4,  8,  30, 9, -10, 0,  0,  30, "xiahong"}},
        {"luoxiahong",   {60,  50,  5,  4,  8,  30, 9, -10, 0,  0,  30, "luoxiahong"}},
        {"xuehong",      {60,  70,  4,  4,  9,  40, 9, -10, 0,  0,  30, "xuehong"}},
        {"shiliuhong",   {60,  70,  4,  4,  9,  40, 9, -10, 0,  0,  30, "shiliuhong"}},
        {"zhenghei",     {70,  60,  1,  4,  1,  10, 3, 5,   20, 5,  45, "zhenghei"}},
        {"hei",          {70,  60,  1,  4,  1,  10, 3, 5,   20, 5,  45, "hei"}},
        {"huihei",       {60,  40,  2,  5,  2,  8,  3, 5,   25, 6,  50, "huihei"}},
        {"mahei",        {80,  60,  1,  6,  2,  10, 4, 5,   25, 7,  45, "mahei"}},
        {"mohei",        {90,  50,  2,  7,  4,  8,  4, 5,   20, 6,  45, "mohei"}},
        {"zaohei",       {90,  70,  1,  8,  4,  10, 4, 5,   25, 8,  50, "zaohei"}},
        {"guozaohei",    {90,  70,  1,  8,  4,  10, 4, 5,   25, 8,  50, "guozaohei"}},
        {"tanhei",       {80,  70,  2,  9,  4,  12, 4, 5,   30, 10, 50, "tanhei"}},
        {"zhengbai",     {40,  30,  3,  1,  2,  30, 5, -10, 0,  0,  30, "zhengbai"}},
        {"bai",          {40,  30,  3,  1,  2,  30, 5, -10, 0,  0,  30, "bai"}},
        {"yabai",        {50,  40,  4,  2,  2,  25, 6, -10, 0,  0,  25, "yabai"}},
        {"danbai",       {40,  50,  5,  2,  2,  30, 6, -10, 0,  0,  35, "danbai"}},
        {"huabai",       {50,  40,  6,  1,  3,  30, 7, -10, 0,  0,  30, "huabai"}},
        {"luhuabai",     {50,  40,  6,  1,  3,  30, 7, -10, 0,  0,  30, "luhuabai"}},
        {"yuebai",       {40,  50,  8,  2,  2,  35, 7, -10, 0,  0,  35, "yuebai"}},
        {"yubai",        {50,  40,  9,  2,  4,  30, 8, -10, 0,  0,  30, "yubai"}},
        {"shitou",       {10,  10,  0,  1,  0,  0,  0, 0,   0,  0,  5, "shitou"}},
        {"qiantou",      {10,  10,  0,  1,  0,  0,  0, 0,   0,  0,  7, "qiantou"}},
        {"yuantou",      {10,  10,  0,  1,  0,  0,  0, 0,   0,  0,  9, "yuantou"}},
        {"jiantou",      {20,  10,  0,  2,  0,  0,  0, 0,   0,  0,  11, "jiantou"}},
        {"fangtou",      {20,  10,  0,  2,  0,  0,  0, 0,   0,  0,  13, "fangtou"}},
        {"datou",        {20,  10,  0,  2,  0,  0,  0, 0,   0,  0,  15, "datou"}},
        {"matou",        {20,  20,  0,  3,  0,  0,  0, 0,   0,  0,  17, "matou"}},
        {"heilian",      {20,  20,  0,  3,  0,  0,  0, 0,   0,  0,  19, "heilian"}},
        {"honge",        {20,  20,  0,  3,  0,  0,  0, 0,   0,  0,  21, "honge"}},
        {"jinding",      {30,  20,  0,  4,  0,  0,  0, 0,   0,  0,  23, "jinding"}},
        {"sanjiantou",   {30,  20,  0,  4,  0,  0,  0, 0,   0,  0,  25, "sanjiantou"}},
        {"baoshitou",    {30,  20,  0,  4,  0,  0,  0, 0,   0,  0,  27, "baoshitou"}},
        {"hupotou",      {30,  30,  0,  5,  0,  0,  0, 0,   0,  0,  30, "hupotou"}},
        {"hudietou",     {30,  30,  0,  5,  0,  0,  0, 0,   0,  0,  32, "hudietou"}},
        {"yuding",       {40,  40,  0,  6,  0,  0,  0, 0,   0,  0,  34, "yuding"}},
        {"qingtingtou",  {40,  40,  0,  7,  0,  0,  0, 0,   0,  0,  36, "qingtingtou"}},
        {"putitou",      {50,  50,  0,  8,  0,  0,  0, 0,   0,  0,  38, "putitou"}},
        {"shouxingtou",  {50,  50,  0,  9,  0,  0,  0, 0,   0,  0,  40, "shouxingtou"}},
        {"yuanchi",      {0,   0,   1,  0,  0,  0,  0, 0,   5,  1,  0, "yuanchi"}},
        {"fangchi",      {0,   0,   1,  0,  0,  0,  0, 0,   7,  1,  0, "fangchi"}},
        {"jianchi",      {0,   0,   1,  0,  0,  0,  0, 0,   9,  1,  0, "jianchi"}},
        {"kuochi",       {0,   0,   2,  0,  0,  0,  0, 0,   11, 2,  0, "kuochi"}},
        {"wubei",        {0,   0,   2,  0,  0,  0,  0, 0,   13, 2,  0, "wubei"}},
        {"qiaochi",      {0,   0,   2,  0,  0,  0,  0, 0,   15, 2,  0, "qiaochi"}},
        {"yinyangchi",   {0,   0,   3,  0,  0,  0,  0, 0,   17, 3,  0, "yinyangchi"}},
        {"lanyi",        {0,   0,   3,  0,  0,  0,  0, 0,   19, 3,  0, "lanyi"}},
        {"changyi",      {0,   0,   3,  0,  0,  0,  0, 0,   21, 3,  0, "changyi"}},
        {"zichi",        {0,   0,   4,  0,  0,  0,  0, 0,   23, 4,  0, "zichi"}},
        {"yinbei",       {0,   0,   4,  0,  0,  0,  0, 0,   25, 4,  0, "yinbei"}},
        {"feichi",       {0,   0,   4,  0,  0,  0,  0, 0,   27, 4,  0, "feichi"}},
        {"bolichi",      {0,   0,   5,  0,  0,  0,  0, 0,   30, 5,  0, "bolichi"}},
        {"wujinchi",     {0,   0,   5,  0,  0,  0,  0, 0,   32, 5,  0, "wujinchi"}},
        {"qingjinchi",   {0,   0,   6,  0,  0,  0,  0, 0,   34, 6,  0, "qingjinchi"}},
        {"pipachi",      {0,   0,   7,  0,  0,  0,  0, 0,   36, 6,  0, "pipachi"}},
        {"ziwuda",       {0,   0,   8,  0,  0,  0,  0, 0,   38, 7,  0, "ziwuda"}},
        {"jinsuoyi",     {0,   0,   9,  0,  0,  0,  0, 0,   40, 7,  0, "jinsuoyi"}},
        {"shuiya",       {0,   0,   0,  0,  1,  5,  1, -3,  0,  0,  0, "shuiya"}},
        {"huaya",        {0,   0,   0,  0,  1,  7,  1, -4,  0,  0,  0, "huaya"}},
        {"huangya",      {0,   0,   0,  0,  1,  9,  1, -5,  0,  0,  0, "huangya"}},
        {"ziya",         {0,   0,   0,  0,  2,  11, 2, -6,  0,  0,  0, "ziya"}},
        {"baiya",        {0,   0,   0,  0,  2,  13, 2, -7,  0,  0,  0, "baiya"}},
        {"hongya",       {0,   0,   0,  0,  2,  15, 2, -8,  0,  0,  0, "hongya"}},
        {"zhimaya",      {0,   0,   0,  0,  3,  17, 3, -9,  0,  0,  0, "zhimaya"}},
        {"zihuaqian",    {0,   0,   0,  0,  3,  19, 3, -10, 0,  0,  0, "zihuaqian"}},
        {"zhiya",        {0,   0,   0,  0,  3,  21, 3, -11, 0,  0,  0, "zhiya"}},
        {"zhadaoya",     {0,   0,   0,  0,  4,  23, 4, -12, 0,  0,  0, "zhadaoya"}},
        {"huadanya",     {0,   0,   0,  0,  4,  25, 4, -13, 0,  0,  0, "huadanya"}},
        {"yuanyangya",   {0,   0,   0,  0,  4,  27, 4, -14, 0,  0,  0, "yuanyangya"}},
        {"heihongqian",  {0,   0,   0,  0,  5,  30, 5, -15, 0,  0,  0, "heihongqian"}},
        {"hongzhuqian",  {0,   0,   0,  0,  5,  32, 5, -16, 0,  0,  0, "hongzhuqian"}},
        {"zhudingqian",  {0,   0,   0,  0,  6,  34, 6, -17, 0,  0,  0, "zhudingqian"}},
        {"baiguya",      {0,   0,   0,  0,  7,  36, 6, -18, 0,  0,  0, "baiguya"}},
        {"tiemenshuan",  {0,   0,   0,  0,  8,  38, 7, -19, 0,  0,  0, "tiemenshuan"}},
        {"wugangqian",   {0,   0,   0,  0,  9,  40, 7, -20, 0,  0,  0, "wugangqian"}},
        {"heiyan",       {0,   0,   0,  0,  0,  15, 3, -5,  15, 3,  15, "heiyan"}},
        {"riyueyan",     {0,   0,   0,  0,  0,  20, 4, -5,  20, 4,  20, "riyueyan"}},
        {"yinyangyan",   {0,   0,   0,  0,  0,  25, 5, -5,  25, 5,  25, "yinyangyan"}},
        {"sanxian",      {10,  10,  2,  2,  2,  0,  0, 0,   0,  0,  0, "sanxian"}},
        {"yixian",       {20,  20,  3,  3,  3,  0,  0, 0,   0,  0,  0, "yixian"}},
        {"baxian",       {30,  30,  4,  4,  4,  0,  0, 0,   0,  0,  0, "baxian"}},
        {"guijia",       {50,  0,   0,  0,  0,  0,  0, 0,   30, 4,  0, "guijia"}},
        {"jinshudai",    {60,  0,   0,  0,  0,  0,  0, 0,   35, 5,  0, "jinshudai"}},
        {"longlinjia",   {70,  0,   0,  0,  0,  0,  0, 0,   40, 6,  0, "longlinjia"}},
        {"yuanyangxu",   {0,   50,  0,  0,  0,  30, 4, -20, 0,  0,  0, "yuanyangxu"}},
        {"zhujiexu",     {0,   60,  0,  0,  0,  35, 5, -20, 0,  0,  0, "zhujiexu"}},
        {"hudiexu",      {0,   70,  0,  0,  0,  40, 6, -20, 0,  0,  0, "hudiexu"}},
        {"tiexiang",     {0,   0,   0,  0,  0,  0,  0, 0,   35, 7,  0, "tiexiang"}},
        {"xuehua",       {0,   0,   0,  0,  0,  0,  0, 0,   40, 8,  0, "xuehua"}},
        {"lanban",       {0,   0,   0,  0,  0,  0,  0, 0,   45, 9,  0, "lanban"}},
        {"sanchajiang",  {0,   0,   0,  7,  0,  0,  0, 0,   0,  0,  35, "sanchajiang"}},
        {"xianchuantui", {0,   0,   0,  8,  0,  0,  0, 0,   0,  0,  40, "xianchuantui"}},
        {"bazhu",        {0,   0,   0,  9,  0,  0,  0, 0,   0,  0,  45, "bazhu"}},
        {"sheban",       {0,   0,   0,  0,  0,  35, 7, -25, 0,  0,  0, "sheban"}},
        {"honglingmen",  {0,   0,   0,  0,  0,  40, 8, -25, 0,  0,  0, "honglingmen"}},
        {"honghaier",    {0,   0,   0,  0,  0,  45, 9, -25, 0,  0,  0, "honghaier"}},
        {"suodu",        {50,  50,  0,  0,  0,  0,  0, 0,   0,  0,  0, "suodu"}},
        {"zaohe",        {70,  70,  0,  0,  0,  0,  0, 0,   0,  0,  0, "zaohe"}},
        {"bake",         {90,  90,  0,  0,  0,  0,  0, 0,   0,  0,  0, "bake"}},
        {"liuyifei",     {0,   0,   12, 0,  0,  0,  0, 0,   35, 5,  0, "liuyifei"}},
        {"chizhao",      {40,  40,  0,  12, 0,  0,  0, 0,   0,  0,  35, "chizhao"}},
        {"dachongya",    {0,   0,   0,  0,  12, 35, 5, -15, 0,  0,  0, "dachongya"}}
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
