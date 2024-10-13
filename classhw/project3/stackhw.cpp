#include<stdio.h>
#include<stdbool.h>
#include<string.h>
const int MAX_T = 1000;
//逆波兰
void pol(void) {
	int stack[MAX_T] = { 0 };
	int top = -1;
	int c;
	while ((c = getchar()) != 10) {
		if (c == '-') {
			int k = -1;
			c = getchar();
			if (c == 10 || c == ' ') {
				int a = stack[top--];
				int b = stack[top--];
				stack[++top] = a - b;
				if (c == 10) {
					break;
				}
			}
			else {
				int a = c - '0';
				while ((c = getchar()) != ' ') {
					a = (a << 3) + (a << 1) + c - '0';
				}
				stack[++top] = k * a;
			}
		}
		if (c >= '0' && c <= '9') {
			int a = c - '0';
			while ((c = getchar()) != ' ') {
				a = (a << 3) + (a << 1) + c - '0';
			}
			stack[++top] = a;
		}
		if (c == '+') {
			int a = stack[top--];
			int b = stack[top--];
			stack[++top] = a + b;
		}
		if (c == '*') {
			int a = stack[top--];
			int b = stack[top--];
			stack[++top] = a * b;
		}
		if (c == '/') {
			int a = stack[top--];
			int b = stack[top--];
			stack[++top] = a / b;
		}
	}
	printf("%d", stack[top]);
}

int getnum(char* get_it,int st, int ed) {
	int stack_i[MAX_T] = { 0 };
	int stack_ju[MAX_T] = { 0 };
	char stack_lis[MAX_T] = { 0 };
	int top_i = -1, top_ju = -1, top_lis = -1;
	int mark = 0,fir = -1;
	for (int i = st; i < ed; i++) {
		if (get_it[i] == '+') {
			stack_ju[++top_ju] = 1;
			continue;
		}
		if (get_it[i] == '-') {
			stack_ju[++top_ju] = -1;
			continue;
		}
		if (get_it[i] >= '0' && get_it[i] <= '9') {
			int a = get_it[i ++] - '0';
			for (; get_it[i] >= '0' && get_it[i] <= '9';i ++) {
				a = (a << 3) + (a << 1) + get_it[i] - '0';
			}
			i--;
			stack_i[++top_i] = a;
			if (top_lis > -1) {
				int a = stack_i[top_i - top_lis - 1];
				for (int j = top_i - top_lis, i = 0;
					i <= top_lis;
					i++, j++) {
					if (stack_lis[top_lis] == '*') {
						a *= stack_i[j];
					}
					if (stack_lis[top_lis] == '/') {
						a /= stack_i[j];
					}
				}
				top_i -= top_lis + 1;
				stack_i[top_i] = a;
				top_lis = -1;
			}
		}
		if (get_it[i] == '*') {
			stack_lis[++top_lis] = '*';
		}
		if (get_it[i] == '/') {
			stack_lis[++top_lis] = '/';
		}
		if (get_it[i] == '(') {
			mark++;
			fir = i ++;
			for (; mark != 0; i++) {
				if (get_it[i] == '(') {
					mark++;
				}
				if (get_it[i] == ')') {
					mark--;
				}
			}
			i--;
			stack_i[++ top_i] = getnum(get_it, fir + 1, i);
			fir = -1;
			if (top_lis > -1) {
				int a = stack_i[top_i - top_lis - 1];
				for (int j = top_i - top_lis, i = 0;
					i <= top_lis;
					i++, j++) {
					if (stack_lis[top_lis] == '*') {
						a *= stack_i[j];
					}
					if (stack_lis[top_lis] == '/') {
						a /= stack_i[j];
					}
				}
				top_i -= top_lis + 1;
				stack_i[top_i] = a;
				top_lis = -1;
			}
		}
	}
	int ans = 0;
	while (top_i >= 0 && top_ju >= 0) {
		ans += stack_i[top_i--] * stack_ju[top_ju--];
	}
	if (top_i >= 0) {
		ans += stack_i[top_i];
	}
	return ans;
}

//正常的
void noma(void) {
	int stack_i[MAX_T] = { 0 };
	int stack_ju[MAX_T] = { 0 };
	int top_i = -1;
	int top_ju = -1;
	char get_it[MAX_T];
	scanf_s("%s", get_it,MAX_T);
	printf("%d", getnum(get_it,0,strlen(get_it)));
}
int main() {
	noma();
	return 0;
}
