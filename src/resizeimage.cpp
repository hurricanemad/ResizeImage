#include "prefix.hpp"

void ReadFilePath(const string& , const string& , const string& , const string& , vector<string>& , vector<string>& );
void ResizeImage(vector<string>&, vector<string>&);

int main(int argc, char **argv) {
    string strSrcPath = "/home/dox/Algorithm/TestImages/PPMImages/";
    string strDstPath = "/home/dox/Algorithm/TestImages/PPMImages321*321/";
    vector<string>vstrSrcFileNames;
    vector<string>vstrDstFileNames;
    
    ReadFilePath(strSrcPath, strDstPath, string("ppm"), string("ppm"), vstrSrcFileNames, vstrDstFileNames);
    ResizeImage(vstrSrcFileNames, vstrDstFileNames);
    
    
    return 0;
}


void ReadFilePath(const string& strSrcPath, const string& strDstPath, const string& strSrcPostFix, const string& strDstPostFix, vector<string>& vstrSrcFileNames, vector<string>& vstrDstFileNames){
    DIR* dirFilePath;
    dirent* direntFilePath;
    size_t sztPathPos;
    
    if(NULL == (dirFilePath=opendir(strSrcPath.c_str()))){
        cerr << "Can't open the file path" << endl;
        exit(-1);
    }
    
    while(NULL != (direntFilePath = readdir(dirFilePath))){
        string strFileName = direntFilePath->d_name;
        size_t sztPos = strFileName.find(strSrcPostFix);
        if((direntFilePath->d_type & DT_DIR) && (0 != strcmp(strFileName.c_str(), ".")) && (0 != strcmp(strFileName.c_str(), ".."))){
            ReadFilePath(strSrcPath, strDstPath, strSrcPostFix, strDstPostFix, vstrSrcFileNames, vstrDstFileNames);            
        }else if(sztPos != string::npos){
            vstrSrcFileNames.push_back(strSrcPath + strFileName);
            string strDstFileName = strFileName.replace(sztPos, max(sizeof(strDstPostFix), sizeof(strSrcPostFix)), strDstPostFix);

            vstrDstFileNames.push_back(strDstPath + strDstFileName);
        }        
    }
    closedir(dirFilePath);
}

void ResizeImage(vector<string>& vstrSrcPath, vector<string>& vstrDstPath){
        if(vstrSrcPath.size() != vstrDstPath.size()){
            cerr<< "The numbers of images in the document is not same!" <<endl;
            exit(-1);
        }
        for(int ni=0; ni < vstrSrcPath.size(); ni++){
            cout << vstrSrcPath[ni] <<endl;
            Mat matSrcImage = imread(vstrSrcPath[ni]);
            Mat matDstImage;
            //resize(matSrcImage, matDstImage, Size(matSrcImage.cols,matSrcImage.rows));
            resize(matSrcImage, matDstImage, Size(321,321));
            cout << vstrDstPath[ni] <<endl; 
            imwrite(vstrDstPath[ni], matDstImage);
        }
}
