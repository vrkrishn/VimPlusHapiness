#include <opencv2/opencv.hpp>
#include <opencv2/contrib/contrib.hpp>

#include <iostream>
#include <sstream>

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <algorithm>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
    vector<Mat> images = vector<Mat>();
    vector<int> labels = vector<int>();

    string base_dir = string("faces");
    DIR *bp, *cp;
    struct dirent *basep, *classp;
    struct stat filestat;

    Size sz;
    //Open base directory
    if ((bp = opendir(base_dir.c_str())) != NULL)
    {
        //Loop through images
        while ((basep = readdir(bp)) != NULL)
        {
            char classbuf[1024];
            sprintf(classbuf, "%s/%s", base_dir.c_str(), basep->d_name);

            if (stat(classbuf, &filestat)) continue;
            if (S_ISDIR(filestat.st_mode)) continue;
            if (basep->d_name[0] == '.') continue;

            if (string(basep->d_name).find("happy") == -1 &&
                string(basep->d_name).find("normal") == -1 &&
                string(basep->d_name).find("sad") == -1 &&
                string(basep->d_name).find("sleepy") == -1)
            {
                continue;
            }

            Mat image = imread(classbuf, CV_LOAD_IMAGE_GRAYSCALE);

            if (image.rows == 0 || image.cols == 0)
                continue;

            images.push_back(image);

            sz = image.size();

            if (string(basep->d_name).find("happy") == -1)
            {
                labels.push_back(0);
            } else {
                labels.push_back(1);
            }
        }
    }

    Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
    model->train(images, labels);
    model->save("model.yml");
}
