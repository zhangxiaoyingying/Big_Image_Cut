#include "RasterIOCut.h"




using namespace std;


/************************************************************************/
/* @biref ͼ����β���                  */
/* @param pszSrcFile   �����ļ�·��
/* @param pszDstFile	����ļ�·��
/* @param iStartX	��ʼ�к�
/* @param iStartY	��ʼ�к�
/* @param iSizeX	��������	
/* @param iSizeY	��������
/* @param 
/* @param 
/************************************************************************/

void ImageCut(const char * pszSrcFile, const char* pszDstFile,int iStartX, int iStartY, 
	int iSizeX, int iSizeY/*, const char* pszFormat*/)
{

	GDALAllRegister();
	GDALDataset *pSrcDS = (GDALDataset*)GDALOpen(pszSrcFile, GA_ReadOnly);
	GDALDataType eDT1 = pSrcDS->GetRasterBand(1)->GetRasterDataType();
		
	const char* Informat;
	GDALDriverH hDriver;

	int iBandCount1 = pSrcDS->GetRasterCount();

	//���ݲ��з�Χȷ�����к��ͼ����
	/*int iDstWidth = iSizeX;
	int iDstHeight = iSizeY;
	*/
	double adfGeoTransform[6] = {0};
	pSrcDS->GetGeoTransform(adfGeoTransform);
	 
	hDriver = GDALGetDatasetDriver(pSrcDS);
	Informat = GDALGetDriverShortName(hDriver);
	//������к��ͼ������Ͻ�����
	adfGeoTransform[0] = adfGeoTransform[0] + iStartX*adfGeoTransform[1] + 
		iStartY*adfGeoTransform[2];
	adfGeoTransform[3] = adfGeoTransform[3] + iStartX*adfGeoTransform[4] + 
		iStartY*adfGeoTransform[5];

	//��������ļ������ÿռ�ο���������Ϣ
	GDALDriver *poDriver = GetGDALDriverManager()->GetDriverByName(Informat);
	GDALDataset * pDstDS = poDriver->Create( pszDstFile, iSizeX, iSizeY, iBandCount1, eDT1, NULL);
	pDstDS->SetGeoTransform(adfGeoTransform);
	pDstDS->SetProjection(pSrcDS->GetProjectionRef());

	//int ysize1=pSrcDS->GetRasterYSize();
	//int xsize1=pSrcDS->GetRasterXSize();

	int *pBandMap = new int[iBandCount1];
	for(int i = 0; i < iBandCount1; i++ )
		pBandMap[i]= i+1;
	//����Ҫ���������������жϣ����벻ͬ���͵Ļ��������д������������8Bitͼ�������ʾ
	if (eDT1 == GDT_Byte)
	{
		//����������������Ҫ�Ļ��棬���ͼ��̫��Ӧ���÷ֿ鴦��
		// ����������������Ҫ�Ļ��棬���ͼ��̫��Ӧ���÷ֿ鴦��

		//char *pDataBuff = new char[iDstWidth*iDstHeight*iBandCount1];	////////////////30000 30000�ڴ����벻������Ҫ�ֿ飡��������10000*10000����
	/*	char *pDataBuff = new char[xsize1/2*ysize1/2*iBandCount1];

		pSrcDS->RasterIO(GF_Read, 0,0,xsize1/2, ysize1/2, pDataBuff, xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		pDstDS->RasterIO(GF_Write, 0, 0,  xsize1/2,  ysize1/2, pDataBuff,  xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);

		pSrcDS->RasterIO(GF_Read, 0,ysize1/2,xsize1/2, ysize1/2, pDataBuff, xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		pDstDS->RasterIO(GF_Write, 0, ysize1/2,  xsize1/2,  ysize1/2, pDataBuff,  xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);

		pSrcDS->RasterIO(GF_Read, xsize1/2,0,xsize1/2, ysize1/2, pDataBuff, xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		pDstDS->RasterIO(GF_Write, xsize1/2, 0,  xsize1/2,  ysize1/2, pDataBuff,  xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);

		pSrcDS->RasterIO(GF_Read, xsize1/2,ysize1/2,xsize1/2, ysize1/2, pDataBuff, xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		pDstDS->RasterIO(GF_Write, xsize1/2, ysize1/2,  xsize1/2,  ysize1/2, pDataBuff,  xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);

*/
		char *pDataBuff = new char[iSizeX*iSizeY*iBandCount1];

		pSrcDS->RasterIO(GF_Read, iStartX,iStartY,iSizeX, iSizeY, pDataBuff, iSizeX,  iSizeY, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		pDstDS->RasterIO(GF_Write, 0, 0,  iSizeX,  iSizeY, pDataBuff,  iSizeX,  iSizeY, eDT1, iBandCount1, pBandMap, 0, 0, 0);

	}

	else
	{
		//
	}

	delete(pBandMap);
	GDALClose((GDALDatasetH)pSrcDS);
	GDALClose((GDALDatasetH)pDstDS);
	
}