#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define base_addr 0x00731c50


HANDLE start() {
	HWND gw =::FindWindow(NULL, "Plants vs. Zombies");
	if (gw == NULL) {
		printf("有没有打开游戏");
		exit(0);
	}
	DWORD pid;
	GetWindowThreadProcessId(gw, &pid);
	if (pid == NULL) {
		printf("获取游戏pid失败");
		exit(0);
	}
	HANDLE proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (pid == NULL) {
		printf("获取游戏句柄失败");
		exit(0);
	}
	return proc;
}

void read(HANDLE proc, int addr) {
	int num;
	LPVOID ret_value = &num;
	ReadProcessMemory(proc, (LPCVOID)addr, ret_value, 8, 0);
	printf("%d\n\n\n", num);
}


int change(HANDLE proc, DWORD cha, int offest1, int offest2) {
	int num;
	LPCVOID addr = (LPCVOID)base_addr;
	LPVOID ret_value = &num;
	ReadProcessMemory(proc, addr, ret_value, 4, 0);
	ReadProcessMemory(proc, (LPCVOID)(num + offest1), ret_value, 4, 0);
	LPVOID fin_sum_addr = (int *)(num + offest2);
	ReadProcessMemory(proc, (LPCVOID)(num + offest2), ret_value, 4, 0);
	WriteProcessMemory(proc, fin_sum_addr, &cha, 4, 0);
}

int change_1(HANDLE proc, int addr, DWORD enable, DWORD disable) {
	int num;
	LPVOID ret_value = &num;
	ReadProcessMemory(proc, (LPCVOID)addr, ret_value, 4, 0);
	if (num == enable) {
		WriteProcessMemory(proc, (LPVOID)addr, &disable, 4, 0);
		printf("关闭了\n\n");
		return 0;
	}
	if (num == disable) {
		WriteProcessMemory(proc, (LPVOID)addr, &enable, 4, 0);
		printf("开启了\n\n");
		return 0;
	}
}

int change_2(HANDLE proc,int addr,unsigned long long enable,unsigned long long disable){
	unsigned long long int num;
	LPVOID ret_value = &num;
	ReadProcessMemory(proc, (LPCVOID)addr, ret_value, 8, 0);
	if (num == enable){
		WriteProcessMemory(proc,(LPVOID)addr,&disable,8,0);
		printf("关闭了\n\n");
		return 0;
	}
	if (num == disable){
		WriteProcessMemory(proc,(LPVOID)addr,&enable,8,0);
		printf("开启了\n\n");
		return 0;
	}
	return 0;
}

void menu() {
	printf("1. 更改阳光            \n");
	printf("2. 更改金币            \n");
	printf("3. 更改巧克力          \n");
	printf("4. 更改杀虫喷雾        \n");
	printf("5. 更改肥料            \n");
	printf("6. 更改智慧树高度      \n");
	printf("7. 无冷却              \n");
	printf("8. 自动收集阳光和金币  \n");
	printf("9. 毁灭菇无弹坑        \n");
	printf("10.蘑菇类白天无需唤醒  \n");
	printf("11.排山倒海            \n");
	printf("12.随意放置            \n");
	printf("13.僵尸禁止            \n");
	printf("14.子弹全部变成玉米棒  \n");
	printf("15.秒杀僵尸            \n");
	printf("16.清除植物            \n");
	printf("17.清除墓碑梯子脑子罐子\n");
	printf("18.浓雾透视			   \n");
	printf("19.透视罐子            \n");
	printf("20.显示隐藏页面        \n");
	printf("21.玉投手只投黄油      \n");
	printf("22.传送带无延迟        \n");
	printf("23.跳关                \n");
	printf("24.解锁所有成就        \n");
	printf("25.退出                \n");
}

void chose(HANDLE proc) {
	int choses;
	printf("请做出你的选择:");
	scanf("%d", &choses);
	switch (choses) {
		case 1: {
			int num;
			LPVOID ret_value = &num;
			ReadProcessMemory(proc, (LPCVOID)0x41f4e5, ret_value, 4, 0);
			if (num == 0x80C70A7E) {
				num = 0x80C70AEB;
				WriteProcessMemory(proc, (LPVOID)0x41f4e5, ret_value, 4, 0);
			}
			printf("要改成多少阳光:");
			scanf("%d", &num);
			change(proc, num, 0x868, 0x5578);
			break;
		}
		case 2: {
			int money;
			printf("要改为多少金币(请输入10的倍数):");
			scanf("%d", &money);
			money = money / 10;
			change(proc, money, 0x94c, 0x54);
			break;
		}
		case 3: {
			int chalt;
			printf("需要改为多少巧克力:");
			scanf("%d", &chalt);
			change(proc, chalt+1000, 0x94c, 0x254);
			break;
		}
		case 4: {
			int num;
			printf("需要改为多少杀虫喷雾:");
			scanf("%d", &num);
			change(proc, num+1000, 0x94c, 0x228);
			break;
		}
		case 5: {
			int num;
			printf("需要改为多少肥料:");
			scanf("%d", &num);
			change(proc, num+1000, 0x94c, 0x224);
			break;
		}
		case 6: {
			int num;
			printf("更改智慧树高度:");
			scanf("%d", &num);
			change(proc, num, 0x94c, 0x120);
			break;
		}
		case 7: {
			DWORD enable = 2113992835;
			DWORD disable = 2116568891;
			int addr = 0x4958c2;
			change_1(proc, addr, enable, disable);
			break;
		}
		case 8: {
			DWORD enable = -74774155;
			DWORD disable = -74774037;
			int addr = 0x4352F2;
			change_1(proc, addr, enable, disable);
			break;
		}
		case 9: {
			DWORD enable = 0x5CE80574;
			DWORD disable = 0x5CE80575;
			int addr = 0x42136d1;
			change_1(proc, addr, enable, disable);
			break;
		}
		case 10: {
			DWORD enable = -125624341;
			DWORD disable = -125624460;
			int addr = 0x4641a2;
			change_1(proc, addr, enable, disable);
			break;
		}
		case 11: {
			DWORD enable = 14910479;
			DWORD disable = 14910735;
			int addr = 0x414007;
			change_1(proc, addr, enable, disable);
			break;
		}
		case 12: {
			DWORD enable = 598505;
			DWORD disable = 153125903;
			int addr = 0x41334f;
			change_1(proc, addr, enable, disable);
			break;
		}
		case 13: {
			DWORD enable = 1182997876;
			DWORD disable = 1182997877;
			int addr = 0x0053f8c3;
			change_1(proc, addr, enable, disable);
			break;
		}
		case 14: {
			unsigned long long enable=0x900000000b5c45c7;
			unsigned long long disable=0x142444db14244489;
			int addr = 0x4747c0;
			change_2(proc, addr, enable, disable);
			break;
		}
		case 15:{
			DWORD enable=0xC68B0C74;
			DWORD disable=0xC68B0C75;
			int addr=0x53f8e5;
			change_1(proc,addr,enable,disable);
			break;
		}
		case 16:{
			DWORD enable=0xB70F9090;
			DWORD disable=0xB70FB074;
			int addr=0x0041F6EE;
			change_1(proc,addr,enable,disable);
			break;
		}
		case 17:{
			DWORD enable=0xB70F9090;
			DWORD disable=0xB70F9674;
			int addr=0x041F9D9;
			change_1(proc,addr,enable,disable);
			break;
		}
		case 18:{
			DWORD enable=0xBA;
			DWORD disable=0xFFBA;
			int addr=0x0041DF37;
			change_1(proc,addr,enable,disable);
			break;
		}
		case 19:{
			DWORD enable=0x90000000324c45c7;
			DWORD disable=0x03358E0F004C7D83;
			int addr=0x004527C4;
			change_2(proc,addr,enable,disable);
			break;
		}
		case 20:{
			DWORD enable =0x47645838;
			DWORD disable=0x47645888;
			int addr=0x431CE0;
			change_1(proc,addr,enable,disable);
			break;
		}
		case 21:{
			DWORD enable =0x168B3F70;
			DWORD disable=0x168B3F75;
			int addr=0x465522;
			change_1(proc,addr,enable,disable);
			break;
		}
		case 22:{
			DWORD enable1 =0x805c4383;
			DWORD disable1=0x835C4BFF;
			DWORD enable2=0xF909090;
			DWORD disable2=0xF005C7B;
			DWORD enable3 =0x3380c083;
			DWORD disable3=0x33480D7E;
			int addr1=0x426847;
			int addr2=0x42684B;
			int addr3=0x498319;
			change_1(proc,addr1,enable1,disable1);
			change_1(proc,addr2,enable2,disable2);
			change_1(proc,addr3,enable3,disable3);
			break;
		}
		case 23:{
			int num1;
			int num2;
			printf("跳转的关卡（请输入 ?-?的形式例如：1-1范围(1-5)-(1-9)）:");
			scanf("%d-%d",&num1,&num2);
			int fin_num=(num1-1)*10+num2;
			change(proc, fin_num, 0x94c, 0x50);
			break;
		}
		case 24:{		
			printf("该功能有问题，暂时停用\n\n");
			/*
			try
				{
					for (int aay = 0; aay < 20; aay++)
					{
						__asm__
						(
							"push ad"
							"mov eax, 7543888"
							"mov eax, dword ptr[eax]"
							"push dword ptr [aay]"
							"push 1"
							"lea edx, [esp]"
							"push edx"
							"push eax"
							"lea ecx, dword ptr[esp + 0xC]"
							"mov esi, 4570112"
							"call esp"
							"add esp, 0x8"
							"pop ad"
						);
					}
				}
				catch(int & e)
				{
				}
				*/
				break;
		}
		case 25:{
			exit(0);
		}
		default:
			printf("Error Choise!!!\n");
			break;
	}
}

int main() {
	system("chcp 936");
	printf("Writen by Evolt\n");
	printf("Test by Wayne\n");
	HANDLE proc = start();
	while (1) {
		menu();
		chose(proc);
	}
	return 0;
}