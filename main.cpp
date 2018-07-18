#include "RasterIOCut.h"
#include <string>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

string dir,dir1,dir_r;
int cost[10][10];

string Int_to_String(int n)
{
	ostringstream stream;
	stream<< n;
	return stream.str();

}


void main()
{
	GDALAllRegister();
	//解决中文路径和字符的乱码问题
	CPLSetConfigOption( "GDAL_FILENAME_IS_UTF8", "NO" );
	CPLSetConfigOption( "SHAPE_ENCODING", "" );

	//dir = "e:\\test_image\\BigMap\\";
	//dir1 = dir + "River_channel.tif";
	//dir_r =  dir + "2_rotate_10.jpg";
	//char SrcFilePath[1000] = "E:\\11\\2\\1.jpg";  //被裁切的图像路径

	char SrcFilePath[1000] ="e:\\test_image\\10k\\Level_17.tif" ;

	const char* srcfile = SrcFilePath;
	/*for (int i=4;i<6;i++)
	{*/
		//char DstFilePath[1000] = "E:\\11\\2\\";	//裁切后图像的路径
		

		int v,w;
		ifstream infile;
		infile.open("C:\\Users\\ZY\\Desktop\\imgdata.txt",ios::in);
		if(!infile.is_open())
			cout<<"open infile failure!"<<endl;

		while(!infile.eof())				//若不是文件结尾，就一直循环
		{
			infile>>v>>w;
			string pp ="e:\\test_image\\BigMap\\" + Int_to_String(v)+"_"+Int_to_String(w) ;
			char DstFilePath[1000]; 
			int i;
			for( i=0;i<pp.length();i++)
			 DstFilePath[i] = pp[i];
			DstFilePath[i] = '\0';
			 
		
	
		char dst[1000];
		
		const char* dstfile = dst;
		int iSizeX1 = 720;	//定义裁切后图像的宽
		int iSizeY1 = 576;	//定义裁切后图像的长
		int iStartX1 =v - 360;//起始坐标
		int iStartY1 =w -288;

		sprintf(dst,"%s.jpg",DstFilePath);

		ImageCut(srcfile,dstfile,iStartX1,iStartY1,iSizeX1,iSizeY1);
	
		}
 /*	}*/
// 	

}
