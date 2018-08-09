#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

void test01()
{
    FILE* pfile = fopen("myfile.txt", "w");
    if(pfile != NULL)
    {
        fputs("世界你好~$$$\n", pfile);
        fprintf(pfile, "北京$$$欢迎您\n");
        fclose(pfile);
    }
}

void test02()
{
    puts("输入一行字符串, 以小数点.结束");
    char ch;
    do 
    {
        ch = getchar();
        putchar(ch);
    } while(ch != '.');
}

void test03()
{
    char buf[1024];
    // gets(buf);
    // 危险! 严禁使用!
    fgets(buf, 256, stdin); // 推荐使用
    printf("%s", buf);
}

void test04()
{
    // int count = 0;
    char ch;
    FILE* pfile = fopen("myfile.txt", "w");
    if(pfile == NULL) perror("fopen");
    else
    {
        for(ch = 'A'; ch <= 'Z'; ch++)
        {
            putc(ch, pfile);
            fputc(ch, pfile);
        }
        fputc('\n', pfile);
        /*
        do
        {
            ch = getc(pfile);
            if(ch == '$')
                count++;
        } while(ch != EOF);
        */
    }
    // printf("$ count is: %d\n", count);
    fclose(pfile);
}

void test05()
{
    char str[64];
    float f;
    FILE* pfile = fopen("myfile.txt", "w+");
    if(pfile == NULL) perror("fopen");
    fprintf(pfile, "%f %s", 3.14159, "pi");
    rewind(pfile);
    fscanf(pfile, "%f", &f);
    fscanf(pfile, "%s", str);
    fclose(pfile);
    printf("I read: %f, %s\n", f, str);
}

void test06()
{
    FILE* pfile;
    char* buf;
    long size;
    size_t ret;
    pfile = fopen("myfile.txt", "rb");
    if(pfile == NULL) fputs("file error", stderr), exit(1);
    fseek(pfile, 0 ,SEEK_END);
    size = ftell(pfile);
    rewind(pfile);
    buf = (char*)malloc(sizeof(char)*size);
    if(buf == NULL) fputs("malloc error", stderr), exit(2);
    ret = fread(buf, 1, size, pfile);
    if(ret != (size_t)size) fputs("fread error", stderr), exit(3);
    fclose(pfile);
    printf("buf: %s\n", buf);
    free(buf);
}

void test07()
{
    FILE* pfile = fopen("myfile.txt", "wb");
    char buf[] = "hello, world";
    fwrite(buf, sizeof(char), sizeof(buf), pfile);
    fclose(pfile);
}

void WriteFile(const char* FileName)
{
    ofstream ofs(FileName, ofstream::out);
    std::string buf = "hello";
    ofs.write(buf.c_str(), buf.length());
    ofs.put('w');
    ofs.put('o');
    ofs.put('r');
    ofs.put('l');
    ofs.put('d');
    ofs.close();
}

void ReadFile(const char* FileName)
{
    ifstream ifs(FileName, ifstream::in);
    char ch;
    cout << "get: ";
    // 一个个字符读取
    while(ifs.get(ch))
    {
        cout << ch;
    }
    cout << endl;
    ifs.close();

    char buf[256];
    ifs.open(FileName, ifstream::in);
    ifs.seekg(ifs.beg);
    ifs.getline(buf, 256);
    cout << "第一行: " << buf << endl;
    ifs.getline(buf, 256);
    cout << "第二行: " << buf << endl;
}

int main()
{
    // test01();
    // test02();
    // test03();
    // test04();
    // test05();
    // test06();
    // test07();

    const char* FileName = "myfile.txt";
    // WriteFile(FileName);
    ReadFile(FileName);
}
