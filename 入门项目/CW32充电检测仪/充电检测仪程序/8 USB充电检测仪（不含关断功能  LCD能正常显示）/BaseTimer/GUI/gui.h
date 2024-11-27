#ifndef _GUI_H_
#define _GUI_H_
#include <stdint.h>
typedef void (*window_func_t)(uint32_t msg);
typedef struct
{
    /* data */
    uint32_t val;
    uint32_t max;
    uint32_t min;
    uint32_t step;
}param_t;
typedef struct 
{
    /* data */
    char *str;
    uint32_t len;
    window_func_t sub_func;
    window_func_t control_func;
}menu_t;
typedef struct 
{
    /* data */
    int y1;

    int y2;
}uirun_t;
typedef struct
{
    /* data */
	  char mode;
    char menu_id; 
    char list_len; 
    menu_t *menuList;
    param_t *paramList;
}window_t;

enum MyEnum
{
    KEY_UP = 1,
    KEY_DOW,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_OK,

    KEY_UP_LONG = 9,
    KEY_DOW_LONG,
    KEY_LEFT_LONG,
    KEY_RIGHT_LONG,
    KEY_OK_LONG,
};
void gui_config(void);
void show_bat(uint16_t bat_v);
void menu_window(uint8_t key_sta);

extern window_func_t run_window;
extern window_func_t run_control;

#define     N_Coloe_B16LightPink                0xFDB8     //24位0xFFB6C1        浅粉红
#define     N_Coloe_B16Pink                     0xFE19     //24位0xFFC0CB        粉红
#define     N_Coloe_B16Crimson                  0xD8A7     //24位0xDC143C        猩红
#define     N_Coloe_B16LavenderBlush            0xFF9E     //24位0xFFF0F5        脸红的淡紫色
#define     N_Coloe_B16PaleVioletRed            0xDB92     //24位0xDB7093        苍白的紫罗兰红色
#define     N_Coloe_B16HotPink                  0xFB56     //24位0xFF69B4        热情的粉红
#define     N_Coloe_B16DeepPink                 0xF8B2     //24位0xFF1493        深粉色
#define     N_Coloe_B16MediumVioletRed          0xC0B0     //24位0xC71585        适中的紫罗兰红色
#define     N_Coloe_B16Orchid                   0xDB9A     //24位0xDA70D6        兰花的紫色
#define     N_Coloe_B16Thistle                  0xDDFB     //24位0xD8BFD8        蓟
#define     N_Coloe_B16plum                     0xDD1B     //24位0xDDA0DD        李子
#define     N_Coloe_B16Violet                   0xEC1D     //24位0xEE82EE        紫罗兰
#define     N_Coloe_B16Magenta                  0xF81F     //24位0xFF00FF        洋红
#define     N_Coloe_B16Fuchsia                  0xF81F     //24位0xFF00FF        灯笼海棠(紫红色)
#define     N_Coloe_B16DarkMagenta              0x8811     //24位0x8B008B        深洋红色
#define     N_Coloe_B16Purple                   0x8010     //24位0x800080        紫色
#define     N_Coloe_B16MediumOrchid             0xBABA     //24位0xBA55D3        适中的兰花紫
#define     N_Coloe_B16DarkVoilet               0xD81C     //24位0x9400D3        深紫罗兰色
#define     N_Coloe_B16DarkOrchid               0x9999     //24位0x9932CC        深兰花紫
#define     N_Coloe_B16Indigo                   0x4810     //24位0x4B0082        靛青
#define     N_Coloe_B16BlueViolet               0x895C     //24位0x8A2BE2        深紫罗兰的蓝色
#define     N_Coloe_B16MediumPurple             0x939B     //24位0x9370DB        适中的紫色
#define     N_Coloe_B16MediumSlateBlue          0x7B5D     //24位0x7B68EE        适中的板岩暗蓝灰色
#define     N_Coloe_B16SlateBlue                0x6AD9     //24位0x6A5ACD        板岩暗蓝灰色
#define     N_Coloe_B16DarkSlateBlue            0x49F1     //24位0x483D8B        深岩暗蓝灰色
#define     N_Coloe_B16Lavender                 0xE73F     //24位0xE6E6FA        熏衣草花的淡紫色
#define     N_Coloe_B16GhostWhite               0xFFDF     //24位0xF8F8FF        幽灵的白色
#define     N_Coloe_B16Blue                     0x001F     //24位0x0000FF        纯蓝
#define     N_Coloe_B16MediumBlue               0x0019     //24位0x0000CD        适中的蓝色
#define     N_Coloe_B16MidnightBlue             0x18CE     //24位0x191970        午夜的蓝色
#define     N_Coloe_B16DarkBlue                 0x0011     //24位0x00008B        深蓝色
#define     N_Coloe_B16Navy                     0x0010     //24位0x000080        海军蓝
#define     N_Coloe_B16RoyalBlue                0x435C     //24位0x4169E1        皇军蓝
#define     N_Coloe_B16CornflowerBlue           0x64BD     //24位0x6495ED        矢车菊的蓝色
#define     N_Coloe_B16LightSteelBlue           0xB63B     //24位0xB0C4DE        淡钢蓝
#define     N_Coloe_B16LightSlateGray           0x7453     //24位0x778899        浅石板灰
#define     N_Coloe_B16SlateGray                0x7412     //24位0x708090        石板灰
#define     N_Coloe_B16DoderBlue                0xD700     //24位0x1E90FF        道奇蓝
#define     N_Coloe_B16AliceBlue                0xF7DF     //24位0xF0F8FF        爱丽丝蓝
#define     N_Coloe_B16SteelBlue                0x4416     //24位0x4682B4        钢蓝
#define     N_Coloe_B16LightSkyBlue             0x867F     //24位0x87CEFA        淡蓝色
#define     N_Coloe_B16SkyBlue                  0x867D     //24位0x87CEEB        天蓝色
#define     N_Coloe_B16DeepSkyBlue              0x05FF     //24位0x00BFFF        深天蓝
#define     N_Coloe_B16LightBLue                0xAEDC     //24位0xADD8E6        淡蓝
#define     N_Coloe_B16PowDerBlue               0xB71C     //24位0xB0E0E6        火药蓝
#define     N_Coloe_B16CadetBlue                0x5CF4     //24位0x5F9EA0        军校蓝
#define     N_Coloe_B16Azure                    0xF7FF     //24位0xF0FFFF        蔚蓝色
#define     N_Coloe_B16LightCyan                0xE7FF     //24位0xE1FFFF        淡青色
#define     N_Coloe_B16PaleTurquoise            0xAF7D     //24位0xAFEEEE        苍白的绿宝石
#define     N_Coloe_B16Cyan                     0x07FF     //24位0x00FFFF        青色
#define     N_Coloe_B16Aqua                     0x07FF     //24位0x00FFFF        水绿色
#define     N_Coloe_B16DarkTurquoise            0x067A     //24位0x00CED1        深绿宝石
#define     N_Coloe_B16DarkSlateGray            0x2A69     //24位0x2F4F4F        深石板灰
#define     N_Coloe_B16DarkCyan                 0x0451     //24位000x8B8B        深青色
#define     N_Coloe_B16Teal                     0x0410     //24位0x008080        水鸭色
#define     N_Coloe_B16MediumTurquoise          0x4E99     //24位0x48D1CC        适中的绿宝石
#define     N_Coloe_B16LightSeaGreen            0x2595     //24位0x20B2AA        浅海洋绿
#define     N_Coloe_B16Turquoise                0x471A     //24位0x40E0D0        绿宝石
#define     N_Coloe_B16Auqamarin                0xA500     //24位0x7FFFAA        绿玉\碧绿色
#define     N_Coloe_B16MediumAquamarine         0x6675     //24位0x00FA9A        适中的碧绿色
#define     N_Coloe_B16MediumSpringGreen        0x07D3     //24位0xF5FFFA        适中的春天的绿色
#define     N_Coloe_B16MintCream                0xF7FF     //24位0x00FF7F        薄荷奶油
#define     N_Coloe_B16SpringGreen              0x07EF     //24位0x3CB371        春天的绿色
#define     N_Coloe_B16SeaGreen                 0x2C4A     //24位0x2E8B57        海洋绿
#define     N_Coloe_B16Honeydew                 0xF7FE     //24位0xF0FFF0        蜂蜜
#define     N_Coloe_B16LightGreen               0x9772     //24位0x90EE90        淡绿色
#define     N_Coloe_B16PaleGreen                0x9FD3     //24位0x98FB98        苍白的绿色
#define     N_Coloe_B16DarkSeaGreen             0x8DF1     //24位0x8FBC8F        深海洋绿
#define     N_Coloe_B16LimeGreen                0x3666     //24位0x32CD32        酸橙绿
#define     N_Coloe_B16Lime                     0x07E0     //24位0x00FF00        酸橙色
#define     N_Coloe_B16ForestGreen              0x2444     //24位0x228B22        森林绿
#define     N_Coloe_B16Green                    0x0400     //24位0x008000        纯绿
#define     N_Coloe_B16DarkGreen                0x0320     //24位0x006400        深绿色
#define     N_Coloe_B16Chartreuse               0x7FE0     //24位0x7FFF00        查特酒绿
#define     N_Coloe_B16LawnGreen                0x7FE0     //24位0x7CFC00        草坪绿
#define     N_Coloe_B16GreenYellow              0xAFE5     //24位0xADFF2F        绿黄色
#define     N_Coloe_B16OliveDrab                0x6C64     //24位0x556B2F        橄榄土褐色
#define     N_Coloe_B16Beige                    0xF7BB     //24位0x6B8E23        米色(浅褐色)
#define     N_Coloe_B16LightGoldenrodYellow     0xFFDA     //24位0xFAFAD2        浅秋麒麟黄
#define     N_Coloe_B16Ivory                    0xFFFE     //24位0xFFFFF0        象牙
#define     N_Coloe_B16LightYellow              0xFFFC     //24位0xFFFFE0        浅黄色
#define     N_Coloe_B16Yellow                   0xFFE0     //24位0xFFFF00        纯黄
#define     N_Coloe_B16Olive                    0x8400     //24位0x808000        橄榄
#define     N_Coloe_B16DarkKhaki                0xBDAD     //24位0xBDB76B        深卡其布
#define     N_Coloe_B16LemonChiffon             0xFFD9     //24位0xFFFACD        柠檬薄纱
#define     N_Coloe_B16PaleGodenrod             0xA060     //24位0xEEE8AA        灰秋麒麟
#define     N_Coloe_B16Khaki                    0xF731     //24位0xF0E68C        卡其布
#define     N_Coloe_B16Gold                     0xFEA0     //24位0xFFD700        金
#define     N_Coloe_B16Cornislk                 0xC000     //24位0xFFF8DC        玉米色
#define     N_Coloe_B16GoldEnrod                0xDD24     //24位0xDAA520        秋麒麟
#define     N_Coloe_B16FloralWhite              0xFFDE     //24位0xFFFAF0        花的白色
#define     N_Coloe_B16OldLace                  0xFFBC     //24位0xFDF5E6        老饰带
#define     N_Coloe_B16Wheat                    0xF6F6     //24位0xF5DEB3        小麦色
#define     N_Coloe_B16Moccasin                 0xFF36     //24位0xFFE4B5        鹿皮鞋
#define     N_Coloe_B16Orange                   0xFD20     //24位0xFFA500        橙色
#define     N_Coloe_B16PapayaWhip               0xFF7A     //24位0xFFEFD5        番木瓜
#define     N_Coloe_B16BlanchedAlmond           0xFF59     //24位0xFFEBCD        漂白的杏仁
#define     N_Coloe_B16NavajoWhite              0xFEF5     //24位0xFFDEAD        Navajo白
#define     N_Coloe_B16AntiqueWhite             0xFF5A     //24位0xFAEBD7        古代的白色
#define     N_Coloe_B16Tan                      0xD5B1     //24位0xD2B48C        晒黑
#define     N_Coloe_B16BrulyWood                0xB000     //24位0xDEB887        结实的树
#define     N_Coloe_B16Bisque                   0xFF38     //24位0xFFE4C4        (浓汤)乳脂,番茄等
#define     N_Coloe_B16DarkOrange               0xFC60     //24位0xFF8C00        深橙色
#define     N_Coloe_B16Linen                    0xFF9C     //24位0xFAF0E6        亚麻布
#define     N_Coloe_B16Peru                     0xCC27     //24位0xCD853F        秘鲁
#define     N_Coloe_B16PeachPuff                0xFED7     //24位0xFFDAB9        桃色
#define     N_Coloe_B16SandyBrown               0xF52C     //24位0xF4A460        沙棕色
#define     N_Coloe_B16Chocolate                0xD343     //24位0xD2691E        巧克力
#define     N_Coloe_B16SaddleBrown              0x8A22     //24位0x8B4513        马鞍棕色
#define     N_Coloe_B16SeaShell                 0xFFBD     //24位0xFFF5EE        海贝壳
#define     N_Coloe_B16Sienna                   0xA285     //24位0xA0522D        黄土赭色
#define     N_Coloe_B16LightSalmon              0xFD0F     //24位0xFFA07A        浅鲜肉(鲑鱼)色
#define     N_Coloe_B16Coral                    0xFBEA     //24位0xFF7F50        珊瑚
#define     N_Coloe_B16OrangeRed                0xFA20     //24位0xFF4500        橙红色
#define     N_Coloe_B16DarkSalmon               0xECAF     //24位0xE9967A        深鲜肉(鲑鱼)色
#define     N_Coloe_B16Tomato                   0xFB08     //24位0xFF6347        番茄
#define     N_Coloe_B16MistyRose                0xFF3C     //24位0xFFE4E1        薄雾玫瑰
#define     N_Coloe_B16Salmon                   0xFC0E     //24位0xFA8072        鲜肉(鲑鱼)色
#define     N_Coloe_B16Snow                     0xFFDF     //24位0xFFFAFA        雪
#define     N_Coloe_B16LightCoral               0xF410     //24位0xF08080        淡珊瑚色
#define     N_Coloe_B16RosyBrown                0xBC71     //24位0xBC8F8F        玫瑰棕色
#define     N_Coloe_B16IndianRed                0xCAEB     //24位0xCD5C5C        印度红
#define     N_Coloe_B16Red                      0xF800     //24位0xFF0000        纯红
#define     N_Coloe_B16Brown                    0xA145     //24位0xA52A2A        棕色
#define     N_Coloe_B16FireBrick                0xB104     //24位0xB22222        耐火砖
#define     N_Coloe_B16DarkRed                  0x8800     //24位0x8B0000        深红色
#define     N_Coloe_B16Maroon                   0x8000     //24位0x800000        栗色
#define     N_Coloe_B16White                    0xFFFF     //24位0xFFFFFF        纯白
#define     N_Coloe_B16WhiteSmoke               0xF7BE     //24位0xF5F5F5        白烟
#define     N_Coloe_B16Gainsboro                0xDEFB     //24位0xDCDCDC        Gainsboro
#define     N_Coloe_B16LightGrey                0xD69A     //24位0xD3D3D3        浅灰色
#define     N_Coloe_B16Silver                   0xC618     //24位0xC0C0C0        银白色
#define     N_Coloe_B16DarkGray                 0xAD55     //24位0xA9A9A9        深灰色
#define     N_Coloe_B16Gray                     0x8410     //24位0x808080        灰色
#define     N_Coloe_B16DimGray                  0x6B4D     //24位0x696969        暗淡的灰色
#define     N_Coloe_B16Black                    0x0000     //24位0x000000        纯黑

#endif
