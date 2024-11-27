#include "gui.h"
#include "lcd_init.h"
#include "lcd.h"
#include "string.h"
#include "adc.h"
#include "app.h"
#include <stdint.h>
#define FONT_W 12
#define FONT_H 26
#define FONT_SIZE 24
typedef struct 
{
    /* data */
    char date[12];
    char version[8];
}version_t;
version_t test_pen_version = {
    __DATE__,"V0.0.01"
};
void main_window(uint32_t key_sta);
void main_control(uint32_t key_sta);
void ttl_window(uint32_t key_sta);
void ttl_control(uint32_t key_sta);
void pwm_window(uint32_t key_sta);
void pwm_control(uint32_t key_sta);
void dc_window(uint32_t key_sta);
void dc_control(uint32_t key_sta);
void onoff_window(uint32_t key_sta);
void onoff_control(uint32_t key_sta);
void diode_window(uint32_t key_sta);
void diode_control(uint32_t key_sta);
void adj_window(uint32_t key_sta);
void adj_control(uint32_t key_sta);
// main menu
menu_t main_menu[7] = {
    {"TTL", 3 * FONT_W, ttl_window, ttl_control},
    {"PWM", 3 * FONT_W, pwm_window, pwm_control},
    {"DC OUT", 6 * FONT_W, dc_window, dc_control},
    {"On/Off", 6 * FONT_W, onoff_window, onoff_control},
    {"Diode", 5 * FONT_W, diode_window, diode_control},
    {"Calibration", 11 * FONT_W, adj_window, adj_control},
    // {"Other",5*FONT_W,}
};
window_t main_Win = {
    0, 
    0,  //默认选第1个
    6, //6级设置
    main_menu, //菜单列表
    NULL,
};
// sub win
menu_t ttl_menu[2] = {
    {"Hight", 40, NULL},
    {"L o w", 24, NULL},
};
param_t ttl_param[2] = {
    {2000, 18000, 0, 100}, //当前值，最大值，最小值，步进值
    {1000, 2000, 0, 100},
};
window_t ttl_Win = {
    0,
    0,
    2, //2级设置
    ttl_menu,
    ttl_param,
};
// pwm win
menu_t pwm_menu[3] = {
    {"Duty", 40, NULL},
    {"KHz", 36, NULL},
    {"Hz", 24, NULL},
};
param_t pwm_param[3] = {
    {50, 100, 0, 1},
    {1, 100, 0, 1},
    {500, 1000, 0, 1},
};
window_t pwm_Win = {
    0,
    0,
    3, //3级设置
    pwm_menu,
    pwm_param,
};
// dcout win
menu_t dc_menu[2] = {
    {"DC", 40, NULL},
};
param_t dc_param[1] = {
    {2000, 5800, 600, 100},
};
window_t dc_Win = {
    0,
    0,
    1,
    dc_menu,
    dc_param,
};
// onoff win
menu_t onoff_menu[2] = {
    {"R", 40, NULL},
};
param_t onoff_param[1] = {
    {100, 200, 0, 1},
};
window_t onoff_Win = {
    0,
    0,
    1,
    onoff_menu,
    onoff_param,
};
// diode win
menu_t diode_menu[1] = {
    {"diode", 5 * FONT_W, NULL},
};
window_t diode_Win = {
    0,
    0,
    1,
    diode_menu,
    NULL,
};
// adj win
menu_t adj_menu[2] = {
    {"adj", 40, NULL},
};
window_t adj_Win = {
    0,
    0,
    1,
    adj_menu,
    NULL,
};
//
window_func_t run_window = NULL;
window_func_t run_control = NULL;
window_t *win_buf = NULL;
uint8_t win_init = 0;
uint8_t select_flag = 1;

int dis_num = 3;   // 最大显示条数
int ui_select = 0; // 当前选择菜单序号

short cursor_x = 8; // 当前坐标x值 2是矩形的x坐标 距离最左边2  字体会在加4后开始绘制
short cursor_y = 2; // 当前坐标y值  文字的坐标是左下角参考点  第一个字 是 0,15
uint16_t bc_color[3] = {0xFF30, N_Coloe_B16LightSkyBlue, N_Coloe_B16LightPink}; //三行的背景色
uint16_t set_light(uint16_t color, uint8_t light) 
{//未调用
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    red = (color & 0xf800) >> 11;
    green = (color & 0x07e0) >> 5;
    blue = (color & 0x001f);

    red = red * light / 10;
    green = red * light / 10;
    blue = red * light / 10;

    red = red > 0x1f ? 0x1f : red;
    green = green > 0x3f ? 0x3f : green;
    blue = blue > 0x1f ? 0x1f : blue;

    return (red << 11) | (green << 5) | (blue);
}
void gui_config(void) //GUI初始化
{
    LCD_Init();//LCD初始化
    LCD_Fill(0, 0, LCD_W, LCD_H, BLACK); //清屏 

    run_window = main_window;  //主窗口界面
    run_control = main_control; //主窗口控制
}
char showbuf[20] = {0};
void show_pen_volt(uint16_t x, uint16_t y, uint16_t volt, uint16_t fc, uint16_t bc) //未调用 不用管
{//未调用 
    uint16_t vt;
    uint16_t mvt;
    vt = (volt / 1000) % 10;
    mvt = (volt % 1000) / 10;
    sprintf(showbuf, "%.1d.%.2dV\0", vt, mvt);
    LCD_ShowString(x, y, showbuf, fc, bc, FONT_SIZE, 0); // RED, BLACK, FONT_SIZE
}
void show_bat_percent(void)
	{ //显示电池电量
    uint16_t bat_val;
    uint16_t percent = 0;
    bat_val = get_bat_val(); //读取电池电压
		
    // 先画电池框
    uint8_t bat_box_x = 142;
    uint8_t bat_box_hight = 7;
    LCD_DrawLine(bat_box_x, 2, bat_box_x, bat_box_hight - 2, BLUE);
    LCD_DrawLine(bat_box_x + 1, 2, bat_box_x + 1, bat_box_hight - 2, BLUE);
    LCD_DrawRectangle(bat_box_x + 2, 0, 160, bat_box_hight, BLUE);
    // 画电量格数
    uint8_t w = 4;        // 显示格子宽
    uint8_t interval = 1; // 格子间的间隔
    uint8_t h = 6;        // 格子的高
    uint8_t y = 1;
    uint8_t y2 = y + h;
    uint8_t x1 = bat_box_x + 3;
    uint8_t x2 = x1 + w + interval;
    uint8_t x3 = x2 + w + interval;
    if (bat_val > 3900) //电池电压>3.9V
    {
        LCD_Fill(x1, y, x1 + w, y2, GREEN);
        LCD_Fill(x2, y, x2 + w, y2, GREEN);
        LCD_Fill(x3, y, x3 + w, y2, GREEN);
    }
    else if (bat_val > 3700)  //电池电压>3.7V
    {
        LCD_Fill(x1, y, x1 + w, y2, bc_color[0]); 
        LCD_Fill(x2, y, x2 + w, y2, GREEN);
        LCD_Fill(x3, y, x3 + w, y2, GREEN);
    }
    else if (bat_val > 3500)  //电池电压>3.5V
    {
        LCD_Fill(x1, y, x2 + w, y2, bc_color[0]);
        LCD_Fill(x3, y, x3 + w, y2, RED);
    }
    else  
    {
        LCD_Fill(x1, y, x3 + w, y2, bc_color[0]);
    }
}
void show_pen_gears(void)
	{ //显示电压测量档位 x1 或x10
    char buf[5];
    sprintf(buf, "x%d \0", pen_gears);
    LCD_ShowString(0, 0, buf, RED, bc_color[0], 12, 0);
}
void clear_window(void)
{ //菜单行清屏
    LCD_Fill(0, 0, LCD_W, 27, bc_color[0]);
    LCD_Fill(0, 27, LCD_W, 27 + 26, bc_color[1]);
    LCD_Fill(0, 53, LCD_W, 80, bc_color[2]);
}
void select_item_color(uint8_t item_id)
{//切换的菜单时 更新底色
    if (select_flag == 1)
    {
        select_flag = 0;
        switch (item_id)
        {
        case 0:
            LCD_Fill(0, 0, LCD_W, 27, BLACK);
            LCD_Fill(0, 27, LCD_W, 27 + 26, bc_color[1]);
            LCD_Fill(0, 53, LCD_W, 80, bc_color[2]);
            break;
        case 1:
            LCD_Fill(0, 0, LCD_W, 27, bc_color[0]);
            LCD_Fill(0, 27, LCD_W, 27 + 26, BLACK);
            LCD_Fill(0, 53, LCD_W, 80, bc_color[2]);
            break;
        case 2:
            LCD_Fill(0, 0, LCD_W, 27, bc_color[0]);
            LCD_Fill(0, 27, LCD_W, 27 + 26, bc_color[1]);
            LCD_Fill(0, 53, LCD_W, 80, BLACK);
            break;
        default:
            LCD_Fill(0, 0, LCD_W, 27, bc_color[0]);
            LCD_Fill(0, 27, LCD_W, 27 + 26, bc_color[1]);
            LCD_Fill(0, 53, LCD_W, 80, bc_color[2]);
            break;
        }
    }
}
void main_window(uint32_t key_sta)
{ //主窗口控制
    if (win_init == 0)
    { //界面切换后第一次进入，初始化相关操作
        logical_level_mode(); //默认TTL模式 控制模拟开关
        win_init = 1;  
        win_buf = &main_Win;
        clear_window();
    }

    int tem = win_buf->menu_id - dis_num + 1;
    if (tem <= 0)
    {
        tem = 0;
    }
    for (int i = 0; i < dis_num; i++)
    {
        if (win_buf->menu_id == (tem + i))
        { //选中的某一行，背景色与字体色相反
            select_item_color(i);
            LCD_ShowString(80 - win_buf->menuList[tem + i].len / 2, cursor_y + i * FONT_H, win_buf->menuList[tem + i].str, bc_color[i], BLACK, FONT_SIZE, 0);
        }
        else
        {
            LCD_ShowString(80 - win_buf->menuList[tem + i].len / 2, cursor_y + i * FONT_H, win_buf->menuList[tem + i].str, BLACK, bc_color[i], FONT_SIZE, 0);
        }
    }
    show_bat_percent(); //显示电池电量
}
void main_control(uint32_t key_sta)
{
    if (win_init == 0)
    {
        win_buf = &main_Win;
    }
    switch (key_sta)
    {
    case KEY_UP:
        if (win_buf->menu_id == 0)
        {
            win_buf->menu_id = win_buf->list_len; // 定位到最后一条，从0开始数的
        }
        win_buf->menu_id--;  //UP键，菜单项向上选
        select_flag = 1; //更新菜单底色标志置位
        break;
    case KEY_DOW:
        win_buf->menu_id++;  //UP键，菜单项向下选
        if (win_buf->menu_id >= win_buf->list_len)
        {
            win_buf->menu_id = 0;
        }
        select_flag = 1; //更新菜单底色标志置位
        break;
    case KEY_LEFT:
        // 开关照明灯 
        toggle_led_light();  //左键，切换照明状态
        break;
    case KEY_RIGHT:
        // 下一级窗口
        win_init = 0; // 为0 表示切换界面  
        run_window = win_buf->menuList[win_buf->menu_id].sub_func; 
        run_control = win_buf->menuList[win_buf->menu_id].control_func;
        select_flag = 1; //更新菜单底色标志置位
        break;
    case KEY_OK:

        break;
    default:
        break;
    }
}
void back_to_main(void)
{// 回到主界面
	  win_init = 0; // 为0 表示切换界面 
    run_window = main_window;
    run_control = main_control;
    select_flag = 1; //更新菜单底色标志置位
}
void num_flash(uint16_t x, uint16_t y, uint16_t num, u8 len, uint16_t fc, uint16_t bc)
{ //数字闪烁
    static uint8_t sta;
    sta++;
    if (sta >= 6)
    {
        sta = 0;
    }
    if (sta > 2) //前三次显示背景色
    {
        LCD_ShowIntNum(x, y, num, len, bc, bc, FONT_SIZE);
    }
    else  //后三次显示字体色
    {
        LCD_ShowIntNum(x, y, num, len, fc, bc, FONT_SIZE);
    }
}
void ttl_volte_to_ble(uint16_t vlote)
{ //蓝牙输出
    static uint16_t cnt = 0;
    cnt++;
    if (cnt >= 10)
    {
        cnt = 0;
        printf("vlote:%u\n", vlote);
    }
}
void ttl_window(uint32_t key_sta)
{//TTL界面
    uint16_t pen_val;
    uint16_t bc;
    uint16_t fc = BLACK;
    if (win_init == 0)
    { //初次进入 TTL模
        logical_level_mode();
        win_init = 1;
        win_buf = &ttl_Win;
        clear_window();
    }
    pen_val = get_pen_val(); //获得笔尖校准后的电压
    for (int i = 0; i < win_buf->list_len; i++)
    {
        if (win_buf->menu_id == i)
        { //被选中菜单，切换前景色与背景色
            fc = bc_color[i + 1];
            bc = BLACK;
            select_item_color(i + 1);
            if (win_buf->mode == 1)
            {
                num_flash(100, cursor_y + (i+1)*FONT_H, win_buf->paramList[i].val, 5, fc, bc);
            }
        }
        else
        {
            fc = BLACK;
            bc = bc_color[i + 1];
        }
        LCD_ShowString(cursor_x, cursor_y + (i + 1) * FONT_H, win_buf->menuList[i].str, fc, bc, FONT_SIZE, 0); //显示菜单名称
        LCD_ShowIntNum(100, cursor_y + (i + 1) * FONT_H, win_buf->paramList[i].val, 5, fc, bc, FONT_SIZE);    //显示参数值
    }
    LCD_ShowIntNum(80 - 3 * 12, cursor_y, pen_val, 5, BLACK, bc_color[0], FONT_SIZE); //显示电压值
    LCD_ShowString(80 + 2 * 12, cursor_y, "mV", BLACK, bc_color[0], FONT_SIZE, 0);  //显示电压单位
    show_bat_percent();  //显示电池电量
    show_pen_gears();  //显示档位
    ttl_volte_to_ble(pen_val); //发送至蓝牙
    // TTL高低电平判断
    if (pen_val >= win_buf->paramList[0].val)
    {
        set_led_green(1);
        set_led_red(0);
    }
    else if (pen_val <= win_buf->paramList[1].val) // 低电平判断
    {
        set_led_red(1);
        set_led_green(0);
    }
    else
    {
        set_led_red(1);
        set_led_green(1);
    }
}
void ttl_control(uint32_t key_sta)
{
    if (win_init == 0)
    {
        win_buf = &ttl_Win;
    }
    switch (key_sta)
    {
    case KEY_UP:
        if (win_buf->mode == 0)
        {
            if (win_buf->menu_id > 0)  //UP键，菜单项向上选
                win_buf->menu_id--;
            select_flag = 1; //更新菜单底色标志置位
        }
        else
        {
            if (win_buf->paramList[win_buf->menu_id].val <
                win_buf->paramList[win_buf->menu_id].max)
            {
                win_buf->paramList[win_buf->menu_id].val += win_buf->paramList[win_buf->menu_id].step;
            }
        }
        break;
    case KEY_DOW:
        if (win_buf->mode == 0)
        {
            win_buf->menu_id++;  //DOWN键，菜单项向下选
            if (win_buf->menu_id >= win_buf->list_len)
            {
                win_buf->menu_id = 0;
            }
            select_flag = 1; //更新菜单底色标志置位
        }
        else
        {
            if (win_buf->paramList[win_buf->menu_id].val >
                win_buf->paramList[win_buf->menu_id].min)
            {
                win_buf->paramList[win_buf->menu_id].val -= win_buf->paramList[win_buf->menu_id].step;
            }
        }
        break;
    case KEY_LEFT:
        // 返回
        back_to_main();
        set_led_red(1);
        set_led_green(1);
        break;
    case KEY_RIGHT:
        win_buf->mode = win_buf->mode > 0 ? 0 : 1;
        break;
    case KEY_OK:

        break;
    default:
        break;
    }
}
void pwm_window(uint32_t key_sta)
{
    uint16_t bc;
    uint16_t fc = BLACK;
    if (win_init == 0)
    {
        pwm_out_mode();
        win_buf = &pwm_Win;
        win_init = 1;
        win_buf->paramList[0].val = get_pwm_duty();
        win_buf->paramList[1].val = get_pwm_hz() / 1000;
        win_buf->paramList[2].val = get_pwm_hz() % 1000;
        clear_window();
    }

    for (int i = 0; i < win_buf->list_len; i++)
    {
        if (win_buf->menu_id == i)
        {
            fc = bc_color[i];
            bc = BLACK;
            select_item_color(i);
            if (win_buf->mode == 1)  //处于参数设置状态 数字闪烁
            {
                num_flash(60, cursor_y + (i)*FONT_H, win_buf->paramList[i].val, 4, fc, bc);
            }
        }
        else
        {
            fc = BLACK;
            bc = bc_color[i];
        }
        LCD_ShowString(cursor_x, cursor_y + (i)*FONT_H, win_buf->menuList[i].str, fc, bc, FONT_SIZE, 0);
        LCD_ShowIntNum(60, cursor_y + (i)*FONT_H, win_buf->paramList[i].val, 4, fc, bc, FONT_SIZE);
    }
    show_bat_percent();
}
void pwm_control(uint32_t key_sta)
{
    if (win_init == 0)
    {
        win_buf = &pwm_Win;
        win_buf->paramList[0].val = get_pwm_duty();
        win_buf->paramList[1].val = get_pwm_hz() / 1000;
        win_buf->paramList[2].val = get_pwm_hz() % 1000;
    }
    switch (key_sta)
    {
    case KEY_UP:
        if (win_buf->mode == 0)
        {
            if (win_buf->menu_id > 0)
                win_buf->menu_id--;
            select_flag = 1; //更新菜单底色标志置位
        }
        else
        {
            if (win_buf->paramList[win_buf->menu_id].val <
                win_buf->paramList[win_buf->menu_id].max)
            {
                win_buf->paramList[win_buf->menu_id].val += win_buf->paramList[win_buf->menu_id].step;
            }
        }
        break;
    case KEY_DOW:
        if (win_buf->mode == 0)
        {
            win_buf->menu_id++;
            if (win_buf->menu_id >= win_buf->list_len)
            {
                win_buf->menu_id = 0;
            }
            select_flag = 1; //更新菜单底色标志置位
        }
        else
        {
            if (win_buf->paramList[win_buf->menu_id].val >
                win_buf->paramList[win_buf->menu_id].min)
            {
                win_buf->paramList[win_buf->menu_id].val -= win_buf->paramList[win_buf->menu_id].step;
            }
        }
        break;
    case KEY_LEFT:
        // 返回
        back_to_main();
        break;
    case KEY_RIGHT:
        if (win_buf->mode == 1 && win_buf->menu_id == 0)
        {
            set_pwm_duty(win_buf->paramList[win_buf->menu_id].val);  //设置占空比
        }
        if (win_buf->mode == 1 && win_buf->menu_id == 1)
        {
            set_pwm_hz(win_buf->paramList[1].val * 1000 + win_buf->paramList[2].val);  //设置频率
        }
        win_buf->mode = win_buf->mode > 0 ? 0 : 1;
        break;
    case KEY_OK:

        break;
    default:
        break;
    }
}
void dc_window(uint32_t key_sta)
{
    uint16_t bc;
    uint16_t fc = BLACK;
    if (win_init == 0)
    {
        dc_out_mode();  //模拟开关设置
        win_buf = &dc_Win;
        win_init = 1;
        win_buf->paramList->val = get_dc_val();
        clear_window();
    }
    for (int i = 0; i < win_buf->list_len; i++)
    {
        if (win_buf->menu_id == i)
        {
            fc = bc_color[i + 1];
            bc = BLACK;
            select_item_color(i + 1);
            if (win_buf->mode == 1)
            {
                num_flash(60, cursor_y + (i + 1) * FONT_H, win_buf->paramList[i].val, 4, fc, bc);
            }
        }
        else
        {
            fc = BLACK;
            bc = bc_color[i + 1];
        }
        LCD_ShowString(cursor_x, cursor_y + (i + 1) * FONT_H, win_buf->menuList[i].str, fc, bc, FONT_SIZE, 0);
        LCD_ShowIntNum(60, cursor_y + (i + 1) * FONT_H, win_buf->paramList[i].val, 4, fc, bc, FONT_SIZE);

        LCD_ShowString(136, cursor_y + (i + 1) * FONT_H, "mV", fc, bc, FONT_SIZE, 0);
    }
    show_bat_percent(); //显示电池电量
}
void dc_control(uint32_t key_sta)
{
    if (win_init == 0)
    {
        win_buf = &dc_Win;
			  win_buf->paramList->val = get_dc_val();  //获取当前DC输出电压值用于显示
    }
    switch (key_sta)
    {
    case KEY_UP:
        if (win_buf->mode == 0)
        {
            if (win_buf->menu_id > 0)
                win_buf->menu_id--;
        }
        else
        {
            if (win_buf->paramList[win_buf->menu_id].val <
                win_buf->paramList[win_buf->menu_id].max)
            {
                win_buf->paramList[win_buf->menu_id].val += win_buf->paramList[win_buf->menu_id].step;
            }
        }
        break;
    case KEY_DOW:
        if (win_buf->mode == 0)
        {
            win_buf->menu_id++;
            if (win_buf->menu_id >= win_buf->list_len)
            {
                win_buf->menu_id = 0;
            }
        }
        else
        {
            if (win_buf->paramList[win_buf->menu_id].val >
                win_buf->paramList[win_buf->menu_id].min)
            {
                win_buf->paramList[win_buf->menu_id].val -= win_buf->paramList[win_buf->menu_id].step;
            }
        }
        break;
    case KEY_LEFT:
        // 返回
        back_to_main();
        break;
    case KEY_RIGHT:
        if (win_buf->mode == 1 && win_buf->menu_id == 0)
        {
            set_dc_val(win_buf->paramList[win_buf->menu_id].val);  //设置DC电压
        }
        win_buf->mode = win_buf->mode > 0 ? 0 : 1;
        break;
    case KEY_OK:
        break;
    default:
        break;
    }
}
const unsigned char oumu[16*21] = {/*--  文字:  Ω  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x03,0x1C,0x07,0x0E,0x0E,0x0F,0x1E,
0x07,0x1E,0x07,0x1C,0x07,0x1E,0x0F,0x1E,0x0E,0x0E,0x1E,0x0F,0x9C,0x07,0xBF,0x1F,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
void onoff_window(uint32_t key_sta)
{
    uint16_t bc;
    uint16_t fc = BLACK;
    uint16_t test_r;
    if (win_init == 0)
    {
        diode_mode();
        win_buf = &onoff_Win;
        win_init = 1;
        clear_window();
    }
    uint16_t pen_val = get_pen_val();
    test_r = (pen_val / 2); //电压为mV,电流为2mA, 电阻单位为欧
    //分段电阻补偿
    if(test_r <4)
    {
        test_r = 0;
    }
    else if (test_r < 85)
    {
        test_r += 6;
    }
    else if (test_r < 106)
    {
        test_r += 5;
    }
    else if (test_r < 157)
    {
        test_r += 4;
    }
    else if (test_r < 177)
    {
        test_r += 3;
    }
    for (int i = 0; i < win_buf->list_len; i++)
    {
        if (win_buf->menu_id == i)
        {
            fc = bc_color[i + 1];
            bc = BLACK;
            select_item_color(i + 1);
            if (win_buf->mode == 1)  //设置参数中，数字闪烁
            {
                num_flash(60, cursor_y + (i + 1) * FONT_H, win_buf->paramList[i].val, 4, fc, bc);
            }
        }
        else
        {
            fc = BLACK;
            bc = bc_color[i + 1];
        }
        LCD_ShowString(cursor_x, cursor_y + (i + 1) * FONT_H, win_buf->menuList[i].str, fc, bc, FONT_SIZE, 0);
        LCD_ShowIntNum(60, cursor_y + (i + 1) * FONT_H, win_buf->paramList[i].val, 4, fc, bc, FONT_SIZE);
        LCD_Show_array(130, cursor_y + FONT_H + 4, 16, 21, fc, bc, oumu);
    }
    // show_pen_volt(60, cursor_y, pen_val, BLACK, bc_color[0]);
    if (test_r > win_buf->paramList[win_buf->menu_id].max)
    {
        LCD_ShowString(60, cursor_y, "  OL", BLACK, bc_color[0], FONT_SIZE,0);
    }
    else
    {
        LCD_ShowIntNum(60, cursor_y, test_r, 4, BLACK, bc_color[0], FONT_SIZE);
    }
    show_bat_percent();
    if (win_buf->paramList[0].val > test_r)    //被测阻值小于设定值，则蜂鸣器响，灯亮
    {
        set_led_green(0); // 亮
        set_fm_onoff(1);  //蜂鸣器响
    }
    else
    {
        set_led_green(1); // 灭
        set_fm_onoff(0);
    }
}
void onoff_control(uint32_t key_sta)
{
    if (win_init == 0)
    {
        win_buf = &onoff_Win;
    }
    switch (key_sta)
    {
    case KEY_UP:
        if (win_buf->mode == 0)
        {
            if (win_buf->menu_id > 0)
                win_buf->menu_id--;
        }
        else
        {
            if (win_buf->paramList[win_buf->menu_id].val <
                win_buf->paramList[win_buf->menu_id].max)
            {
                win_buf->paramList[win_buf->menu_id].val += win_buf->paramList[win_buf->menu_id].step;
            }
        }
        break;
    case KEY_DOW:
        if (win_buf->mode == 0)
        {
            win_buf->menu_id++;
            if (win_buf->menu_id >= win_buf->list_len)
            {
                win_buf->menu_id = 0;
            }
        }
        else
        {
            if (win_buf->paramList[win_buf->menu_id].val >
                win_buf->paramList[win_buf->menu_id].min)
            {
                win_buf->paramList[win_buf->menu_id].val -= win_buf->paramList[win_buf->menu_id].step;
            }
        }
        break;
    case KEY_LEFT:
        // 返回
        back_to_main();
        set_led_green(1); // 灭
        set_fm_onoff(0);
        break;
    case KEY_RIGHT:
        win_buf->mode = win_buf->mode > 0 ? 0 : 1;  //电阻设置状态切换
        break;
    case KEY_OK:

        break;
    default:
        break;
    }
}
void diode_window(uint32_t key_sta)
	{ //测量二级管导通电压
    uint16_t bc;
    uint16_t fc = BLACK;
    if (win_init == 0)
    {
        diode_mode(); //切换二极管模式
        win_buf = &diode_Win;
        win_init = 1;
        clear_window(); 
    }
    uint16_t pen_val = get_pen_val(); //获取笔尖电压
    if(pen_val > 2500)
    { //电压大于2.5V，调整偏差
        pen_val -= 50; 
    }
    for (int i = 0; i < win_buf->list_len; i++)
    {
        bc = bc_color[i + 1];
        LCD_ShowString(cursor_x, cursor_y + (i + 1) * FONT_H, win_buf->menuList[i].str, fc, bc, FONT_SIZE, 0);
        LCD_ShowIntNum(win_buf->menuList[0].len + FONT_W, cursor_y + (i + 1) * FONT_H, pen_val, 5, fc, bc, FONT_SIZE);
    }
    LCD_ShowString(134, cursor_y + FONT_H, "mV", BLACK, bc_color[1], FONT_SIZE, 0); //显示单位
    show_bat_percent(); //显示电池电量 
}
void diode_control(uint32_t key_sta)
{
    if (win_init == 0)
    {
        win_buf = &diode_Win;
    }
    switch (key_sta)
			{ //无参数设置，不需要UP DOWN键，按LEFT返回
    case KEY_LEFT:
        // 返回
        back_to_main();  
        break;
    case KEY_RIGHT:
        break;
    case KEY_OK:

        break;
    default:
        break;
    }
}
void adj_window(uint32_t key_sta)
{
    uint8_t ret = 0;
    if (win_init == 0)
    {
        win_buf = &adj_Win;
        win_init = 1;
        logical_level_mode();//切换到TTL模式，进行笔尖电压采集
        clear_window();
        switch_auto_disable(1); //自动档位切换关闭
        set_multiple_xn(1);//先校准x1档
        clear_adc_ref_cnt(); //清除计数
    }
    LCD_ShowString(cursor_x, cursor_y, "calibration", BLACK, bc_color[0], FONT_SIZE, 0);
    LCD_ShowString(cursor_x, cursor_y + FONT_H, "wait", BLACK, bc_color[1], FONT_SIZE, 0);
    do
    {
        ret = adc_soft_Calibration(1);//校准处理
			} while (ret == 0); //ret为1时表示校准完成
    set_multiple_xn(10); // 校准x10档
    clear_adc_ref_cnt();
    do
    {
        ret = adc_soft_Calibration(10);
    } while (ret == 0);
    switch_auto_disable(0); //自动档位切换打开
    clear_adc_ref_cnt();
    save_adc_ref_val(); //参数存储
    back_to_main();  //校正完成后，直接返回主界面
}
void adj_control(uint32_t key_sta)
{
    if (win_init == 0)
    {
        win_buf = &adj_Win;
    }
    switch (key_sta)
    {
    case KEY_UP:

        break;
    case KEY_DOW:

        break;
    case KEY_LEFT:
        // 返回
        break;
    case KEY_RIGHT:

        break;
    case KEY_OK:

        break;
    default:
        break;
    }
}
