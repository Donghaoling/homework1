#include <opencv2/opencv.hpp>   
#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <string>
#include <vector>
using namespace std;
using namespace cv;
#pragma comment(lib,"User32.lib")

int main(int argc,TCHAR *argv[]) {
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	TCHAR szDir[MAX_PATH];
	size_t length_of_arg;
	HANDLE hFind=INVALID_HANDLE_VALUE;
	DWORD dwError=0;
	
	vector<string> jpgFileDir;

	//Check argument length. If wrong, print usage.
	if(argc !=4){
		_tprintf(TEXT("\nUsage: %s <directory name> <delay> <AVI name.avi>"),argv[0]);
		return (-1);
	}

	//Output the parameter input into the system
	_tprintf(TEXT("\nSource directory is %s\n"),argv[1]);
	_tprintf(TEXT("\nDelay is set to %s\n"),argv[2]);
	_tprintf(TEXT("\nTarget AVI is %s\n\n"),argv[3]);

	StringCchCopy(szDir, MAX_PATH, argv[1]);
    StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

	//find the first file in the directory
	hFind = FindFirstFile(szDir, &ffd);

    if (INVALID_HANDLE_VALUE == hFind){
		_tprintf(TEXT("FindFirstFile"));
		return dwError;
	} 

	// List all the files in the directory with some info about them.
    do{
       if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
          //_tprintf(TEXT("  %s   <DIR>\n"), ffd.cFileName);
       }
       else{
         /* filesize.LowPart = ffd.nFileSizeLow;
          filesize.HighPart = ffd.nFileSizeHigh;*/
          //_tprintf(TEXT("  %s   %ld bytes\n"), ffd.cFileName, filesize.QuadPart);
			string sfilename,sfiledir;
			sfilename=ffd.cFileName;
			//cout<<sfilename<<endl;
			sfilename = "\\"+sfilename;
			sfiledir=argv[1]+sfilename;
			//cout<<sfiledir<<endl;
			jpgFileDir.push_back(sfiledir);
       }
    }
    while (FindNextFile(hFind, &ffd) != 0);

	

	dwError = GetLastError();
    if (dwError != ERROR_NO_MORE_FILES) {
       _tprintf(TEXT("FindFirstFile"));
	}

    
	
	CvCapture *capture = 0;
	CvSize size=cvSize(1024,960);//视频帧格式的大小
	double fps=3;
	string sdir1=argv[1];
	string sdir2=argv[3];
	string sdir=sdir1+"\\"+sdir2;
	cout<<sdir;
	CvVideoWriter *writer = cvCreateVideoWriter(
		sdir.c_str(),
		CV_FOURCC('M','J','P','G'),
		fps,
		size
	);
	int n=jpgFileDir.size();
	//cout<<"aaaa"<<n;
	
	cvNamedWindow("Homework",CV_WINDOW_AUTOSIZE);  
	for(int i=0;i<n;i++){
		string sJpgDir = jpgFileDir.back();		
		cout<<sJpgDir<<endl;
		jpgFileDir.pop_back();
		IplImage *src;     
		src = cvLoadImage(sJpgDir.c_str());
		if(!src)  break;
		IplImage *src_resize = cvCreateImage(size,8,3); //创建视频文件格式大小的图片
		
		  
		cvShowImage("Homework",src);    
		cvWaitKey(0);
		cvResize(src,src_resize);
		cvWriteFrame(writer,src_resize);
		cvDestroyWindow("Homework");  
		cvReleaseImage(&src);
	}
	FindClose(hFind);
    return dwError;
	system("pause");

   /* 
    IplImage *src;     
    src = cvLoadImage("desert.jpg");     
    cvNamedWindow("bvin",CV_WINDOW_AUTOSIZE);    
    cvShowImage("bvin",src);    
    cvWaitKey(0);    
    cvDestroyWindow("bvin");  
    cvReleaseImage(&src); 
	*/
 
}