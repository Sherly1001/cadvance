#ifndef __compress_h__
#define __compress_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

// phan tich xau dau vao str, dua ra cac tu ma va tan so xuat hien cac tu ma
// ket ua luu vao mang myCode
// myCodeSize la so luong tu ma trong xau str
void processinput(const char *str, WCode myCode[128], int *myCodeSize);

TREENODE *buildHuffmanTree(WCode myCode[128], int myCodeSize);

void treeTravel(TREENODE *root, char rootcode[]);

#endif