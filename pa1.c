#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

typedef struct tmp
{
	char item[46];
	struct tmp *next;
} Node;
//structure for create linked list.
typedef struct
{
	Node *head;
	Node *tail;
	int numoflist;
} List;

//Initialize List
void initList(List *lp)
{
	lp->head = NULL;
	lp->tail = NULL;
	lp->numoflist = 0;
}
char *strcat(char *dst, char *src)
{
	char *tmp = dst;

	while (*dst)
		dst++;

	while ((*dst++ = *src++) != '\0')
		;
	return tmp;
}
void itoa(int num, char *str)
{
	int deg = 1;
	int pow = 0;

	if (num == 0)
	{
		str[0] = num + '0';
		str[1] = '\0';
		return;
	}

	while (1)
	{
		if ((num / deg) > 0)
			pow++;
		else
			break;
		deg *= 10;
	}
	deg /= 10;
	for (int i = 0; i < pow; i++)
	{
		str[i] = num / deg + '0';
		num -= ((num / deg) * deg);
		deg /= 10;
	}
	str[pow] = '\0';
}
int strlength(const char *str)
{
	unsigned int len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return len;
}
void *strcp(char *dst, const char *src)
{
	char *temp = dst;

	while ((*dst++ = *src++) != '\0')
		dst[strlength(src)] = '\0';
	return temp;
}

//Create node and return reference of it.
Node *createNode(char *item)
{
	Node *nNode;

	nNode = (Node *)malloc(sizeof(Node));

	strcp(nNode->item, item);
	nNode->next = NULL;

	return nNode;
}

void print(char *str)
{
	char newline[] = "\n";
	write(1, str, strlength(str));
	write(1, newline, 1);
}
void *memoryset(void *pDes, int value, size_t size)
{
	char *temp = (char *)pDes;

	while (size--)
		*temp++ = value;

	return pDes;
}

//Add new item at the end of list.
void insert(List *lp, char *item)
{

	Node *node;
	node = createNode(item);

	//if list is empty.
	if (lp->head == NULL)
	{
		lp->head = node;
		lp->tail = node;
	}
	else
	{
		lp->tail->next = node;
		lp->tail = lp->tail->next;
	}
	(lp->numoflist)++;
}
void printList(List *pl)
{
	char newline[] = "\n";
	Node *cur = pl->head;
	while (cur != NULL)
	{
		write(1, cur->item, strlength(cur->item));
		cur = cur->next;
	}
	write(1, newline, 1);
	write(1, newline, 1);
}
void dPrint(int d)
{
	char newline[] = "\n";
	char num[12] = "";
	itoa(d, num);
	write(1, num, strlength(num));
	write(1, newline, 1);
}
void Write(int line, int idx)
{
	char num[12] = "";
	char index[4] = "";
	itoa(line, num);
	strcat(num, ":");
	itoa(idx + 1, index);
	strcat(num, index);
	strcat(num, "\n");
	write(1, num, strlength(num));
}
int strcmp(const char *str1, const char *str2)
{
	char c1, c2;
	int len1, len2;

	len1 = strlength(str1);
	len2 = strlength(str2);

	if (len1 != len2)
		return 1;

	while (1)
	{
		c1 = *str1++;
		c2 = *str2++;

		if (c1 != c2)
			return 1;

		if (!c1)
			break;
	}
	return 0;
}

int getLine(int fd, List *txtList)
{
	char buffer[1] = "";
	char txt[46];
	int i = 0;
	ssize_t rd;
	ssize_t rdsize;
	int s = 0;
	while (1)
	{
		if (rdsize = read(fd, buffer, 1) > 0)
		{
			s++;
			if (buffer[0] == ' ' || buffer[0] == '\t')
			{
				txt[i++] = '\0';
				insert(txtList, txt);
				memoryset(txt, '\0', strlength(txt));
				i = 0;
				continue;
			}
			else if (buffer[0] == '\n')
			{
				txt[i] = '\0';
				insert(txtList, txt);

				memoryset(txt, '\0', strlength(txt));

				i = 0;
				return s;
			}
			else
				txt[i++] = buffer[0];
		}
		else
			return -1;
	}
}
void case1(int fd, List *iplist)
{
	int line = 1;
	while (1)
	{
		List txtList;
		initList(&txtList);
		int result = getLine(fd, &txtList);

		if (result < 0)
			break;
		int i = 0;
		Node *cur = txtList.head;

		while (cur != NULL)
		{
			char txt[45];
			char ip[45];
			strcp(ip, iplist->head->item);
			strcp(txt, cur->item);

			if (strcmp(txt, ip) == 0)
			{
				Write(line, i);
			}

			cur = cur->next;
			i++;
		}

		line++;
	}
}
char *strstr(char *s1, const char *s2)
{
	int i;
	
	if(*s2=='\0')
		return (char *)s1;

	else{
		 for(;*s1;s1++){
		
			 if(*s1==*s2){
				 for(i=1;*(s1+i)==*(s2+i);i++); 
			 		if(i==strlength(s2))
			 		return (char *)s1;
			 } 
		}
		return NULL;
	}
}

void case2(int fd, List *iplist)
{
	int line = 1;

	while (1)
	{

		int i = 0;
		int c =0;
		List txtList;
		initList(&txtList);
		int result = getLine(fd, &txtList);
		char *ptr = NULL;
		if (result < 0)
			break;
		Node *txtcur = txtList.head;
		Node *ipcur = iplist->head;
		int k =0;
		while(ipcur != NULL)
		{
			while(txtcur != NULL)
			{
				if(strcmp(txtcur->item, ipcur->item)==0)
					{
						txtcur = txtList.head;
						k++;
						break;
					}
				txtcur = txtcur->next;
			}
			ipcur = ipcur->next;
		}
		if(k==iplist->numoflist)
			dPrint(line);
		line++;
	}
}
void case3(int fd, List *iplist)
{
	int line = 1;

	while (1)
	{

		int i = 0;
		List txtList;
		initList(&txtList);
		int result = getLine(fd, &txtList);
		if (result < 0)
			break;
		Node *txtcur = txtList.head;
		Node *ipcur = iplist->head;

		int c = 0;
		while (txtcur != NULL)
		{
			int c =0;
			int k;		
			for(k=0; k<iplist->numoflist; k++)
				{
					if(ipcur == NULL || txtcur ==NULL)
						break;
					if(strcmp(ipcur->item, txtcur->item) ==0)
					{		
							ipcur = ipcur->next;
							if(txtcur->next ==NULL);								
							else
								txtcur = txtcur->next;	
							i++;
					}
					else if(strcmp(ipcur->item, txtcur->item) !=0)
						break;
				}
				if(k==iplist->numoflist)
				{
					Write(line, i-iplist->numoflist);
				}

			ipcur = iplist->head;
			txtcur = txtcur->next;
			i++;		
		}
		line++;
	}
}
void case4(int fd, List *iplist)
{
	int line = 1;

	while (1)
	{

		int i = 0;
		List txtList;
		initList(&txtList);
		int result = getLine(fd, &txtList);
		if (result < 0)
			break;
		Node *txtcur = txtList.head;
		Node *ipcur = iplist->head;

		int c = 0;
		while (txtcur != NULL)
		{
			if (strcmp(txtcur->item, ipcur->item) == 0)
			{
				if(txtcur->next ==NULL)
					break;
				txtcur = txtcur->next;
				ipcur = ipcur->next;
				if (txtcur->next != NULL && ipcur != NULL && strcmp(txtcur->next->item, ipcur->item) == 0)
				{
					ipcur = iplist->head;
					Write(line, i);
				}
				else i++;
			}
			ipcur = iplist->head;
			txtcur = txtcur->next;
			i++;
		}

		line++;
	}
}
int main(int argc, char **argv)
{
	List iplist;
	initList(&iplist);
	int fd;
	 if ((fd = open(argv[1], O_RDONLY)) < 0)
        {
			char err[45] ="file open err";
			print(err);
                exit(1);
        }
	char buffer[19] = "Enter Keyword(s) : ";
	write(1, buffer, 19);

	char buff[1];
	char input[46];
	int case_num = 0;
	int i = 0;
	while (read(0, buff, 1))
	{
		if (buff[0] == '\n')
		{
			input[i++] = '\0';
			insert(&iplist, input);
			memoryset(input, '\0', strlength(input));
			break;
		}
		else if (buff[0] == '\"')
		{
			case_num = 3;
		}
		else if (buff[0] == '*')
		{
			case_num = 4;
		}
		else if ((buff[0] == ' ' || buff[0] == '\t') && case_num != 3 && case_num != 4)
		{
			case_num = 2;
			input[i++] = '\0';
			insert(&iplist, input);
			memoryset(input, '\0', strlength(input));
			i = 0;
		}
		else if (buff[0] == '\"')
			;
		else if ((buff[0] == ' ' || buff[0] == '\t') && case_num == 4)
			;
		else if ((buff[0] == ' ' || buff[0] == '\t') && case_num == 3)
		{
			input[i++] = '\0';
			insert(&iplist, input);
			memoryset(input, '\0', strlength(input));
			i = 0;
		}
		else
			input[i++] = buff[0];
	}
	if (case_num == 0)
		case_num = 1;
	
	switch (case_num)
	{
	case 1:
		case1(fd, &iplist);
		close(fd);
		break;
	case 2:
		case2(fd, &iplist);
		close(fd);
		break;
	case 3:
		case3(fd, &iplist);
		close(fd);
		break;
	case 4:
		case4(fd, &iplist);
		close(fd);
		break;
	}
	close(fd);
	return 0;
}

