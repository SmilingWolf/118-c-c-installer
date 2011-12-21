/* The whole code you can see here was written by Lupo96 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ogcsys.h>
#include <gccore.h>
#include <ogc/isfs.h>

#include "../build/00000000_app.h"
#include "../build/00000001_app.h"
#include "../build/00000002_app.h"
#include "../build/title_tmd.h"
#include "../build/31313843_tik.h"

void delete_channel_118() {
	s32 ret;
	ret = ISFS_Delete("/title/00010001/31313843/content/00000000.app");
	if (ret < 0) {
		printf("\nCan't delete content 0");
	}
	ret = ISFS_Delete("/title/00010001/31313843/content/00000001.app");
	if (ret < 0) {
		printf("\nCan't delete content 1");
	}
	ret = ISFS_Delete("/title/00010001/31313843/content/00000002.app");
	if (ret < 0) {
		printf("\nCan't delete content 2");
	}
	ret = ISFS_Delete("/title/00010001/31313843/content/title.tmd");
	if (ret < 0) {
		printf("\nCan't delete title");
	}
	ret = ISFS_Delete("/ticket/00010001/31313843.tik");
	if (ret < 0) {
		printf("\nCan't delete ticket");
	}
	printf("\nDone.\n");
}

void createdir_channel_118() {
	s32 ret;
	ret = ISFS_CreateDir("/title/00010001/31313843", 0, ISFS_OPEN_RW, ISFS_OPEN_RW, ISFS_OPEN_READ);
	if (ret < 0) {
		printf("\nCannot create 118Channel main directory, ret = %d", ret);
	}
	ret = ISFS_CreateDir("/title/00010001/31313843/content", 0, 3, 3, 0);
	if (ret < 0) {
		printf("\nCannot create 118Channel content directory, ret = %d", ret);
	}
	ret = ISFS_CreateDir("/title/00010001/31313843/data", 0, 3, 3, 0);
	if (ret < 0) {
		printf("\nCannot create 118Channel data directory, ret = %d", ret);
	}
	printf("\nDone.\n");
}

void check_channel_118() {
	s32 ret;
	ret = ISFS_Open("/ticket/00010001/31313843.tik", ISFS_OPEN_READ);
	if (ret < 0) {
		printf("\nThe 118 Channel is not installed yet!\n");
		printf("Creating directory structure... ");
		createdir_channel_118();
	}
	else 
	{
		ISFS_Close(ret);
		printf("Uninstalling previous version of the 118 Channel...\n");
		delete_channel_118();
	}
}

void install_all(const u8 *source, char* destination, u32 filesize)
{
	s32 ret;
	ISFS_CreateFile(destination, 0, 3, 3, 0);
	s32 fd = ISFS_Open(destination, ISFS_OPEN_RW);
	ret = ISFS_Write(fd, source, filesize);
	if (ret < 0 )
	{
		ISFS_Close(fd);
		printf("Write failed. ret %d\n",ret);
		printf("Write of content app failed. ");
	}
	ISFS_Close(fd);
}

void install_channel_118() {
	ISFS_Initialize();
	printf("Checking if 118 Channel is installed...\n\n");
	check_channel_118();
	printf("Installing 118 Channel...\n\n");
	printf("Writing /title/00010001/31313843/content/00000000.app... ");
	install_all(_00000000_app, "/title/00010001/31313843/content/00000000.app", _00000000_app_size);
	printf("done.\nWriting /title/00010001/31313843/content/00000001.app... ");
	install_all(_00000001_app, "/title/00010001/31313843/content/00000001.app", _00000001_app_size);
	printf("done.\nWriting /title/00010001/31313843/content/00000002.app... ");
	install_all(_00000002_app, "/title/00010001/31313843/content/00000002.app", _00000002_app_size);
	printf("done.\nWriting /title/00010001/31313843/content/title.tmd... ");
	install_all(title_tmd, "/title/00010001/31313843/content/title.tmd", title_tmd_size);
	printf("done.\nWriting /ticket/00010001/31313843.tik... ");
	install_all(_31313843_tik, "/ticket/00010001/31313843.tik", _31313843_tik_size);
	printf("done.\n");
}