#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <string>
#include <string.h>
#include <cstring>
#include <vector>
#include <cstdlib>
using namespace std;
using namespace cv;
#pragma comment(lib,"User32.lib")

int main(int argc,TCHAR *argv[]) {
	WIN32_FIND_DATA ffd;
	//LARGE_INTEGER filesize;
	TCHAR szDir[MAX_PATH];
	//size_t length_of_arg;
	HANDLE hFind=INVALID_HANDLE_VALUE;
	DWORD dwError=0;
	
	vector<string> jpgFileDir;

	//Check argument length. If wrong, print usage.
	if(argc !=4){
		_tprintf(TEXT("\nUsage: %s <directory name> <delay> <AVI name.avi>"),argv[0]);
		return (-1);
	}

	int delay=1;
	TCHAR delayBuffer[MAX_PATH];
	StringCchCopy(delayBuffer,MAX_PATH,argv[2]);
	string sDelay=delayBuffer;
	delay=atoi(sDelay.c_str());

	//cout<<delay<<endl;

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
	//cout<<jpgFileDir.size()<<endl;

	//CvCapture *capture = 0;
	Size size=cvSize(640,480);//视频帧格式的大小
	double fps=60.0;
	string sdir1=argv[1];
	string sdir2=argv[3];
	string sdir="e:\\images\\"+sdir2;
	//cout<<sdir<<endl;
	VideoWriter writer=VideoWriter(sdir.c_str(),CV_FOURCC('M','J','P','G'),60.0,size,TRUE);
	int n=jpgFileDir.size();
	cout<<"n:"<<n<<endl;
  
	for(int i = 0;i < fps*delay;i++){
		//Mat tempfirstPage=imread(jpgFileDir.front());
		Mat firstPage(size,CV_8UC3);//初始化一个大小为size的Mat
		//resize(tempfirstPage,firstPage,size,1.0,1.0,INTER_AREA);
		putText(firstPage,"21421276",Point(120,150),FONT_ITALIC,2,Scalar(0,0,0),3);
		putText(firstPage,"Haoling Dong",Point(100,350),FONT_ITALIC,2,Scalar(0,0,0),3);
		writer << firstPage;
	}

	for(int i=0;i<7;i++){
		int nFrames=0;
		string sJpgDir = jpgFileDir[i];
		Mat src=imread(sJpgDir);
		cout<<sJpgDir<<endl;
		while(nFrames<(fps*delay)){								
			Mat src_resize;
			resize(src,src_resize,size,1.0,1.0,INTER_AREA);//将图片大小调整为视频支持的大小
			writer<<src_resize;
			nFrames++;
		}
	}
    return 0;
}


