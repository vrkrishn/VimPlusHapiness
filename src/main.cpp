#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/contrib/contrib.hpp>


#include <iostream>
#include <sstream>

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <algorithm>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
    Mat frame_orig, back, fore;

    VideoCapture cap;
    cap.open(0);


    Size sz = Size(320, 243);
    Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
    model->load(argv[1]);

    namedWindow("Frame");

    if( !cap.isOpened() )
    {
        cout << "***Could not initialize capturing...***\n";
        cout << "Current parameter's value: \n";
        return -1;
    }

    int keyboard = 0;

    int SMILE_IN_A_ROW = 3;
    int current = 0;

    int i = 0;
    while((char) keyboard != 27)
    {
        //Get the frame
        cap >> frame_orig;
        if (frame_orig.empty())
        {
            cerr << "Failed to capture frame\n";
            break;
        }
        cvtColor(frame_orig, frame_orig, CV_BGR2GRAY);

        int width = frame_orig.cols;
        int heigth = frame_orig.rows;
        int off_w = width/4;
        int off_h = heigth/3;

        rectangle(frame_orig, Point(width/2 - off_w, heigth/2 - off_h),
                              Point(width/2 + off_w, heigth/2 + off_h),
                              Scalar(255,0,0), 4);

        Mat selection = frame_orig(cv::Rect(width/2 - off_w, heigth/2 - off_h, 2*off_w, 2*off_h));
        Mat frame;
        selection.copyTo(frame);

        resize(frame, frame, sz);

        imshow("Frame", frame);
        if (i % 10 == 0)
        {
            int result = model->predict(frame);
            if (result == 1)
            {
                current++;
                if (current <= SMILE_IN_A_ROW)
                    cout << "Smile for " << SMILE_IN_A_ROW-current << " more seconds" << endl;
            } else {
                current = 0;
                cout << "You frowned start over" << endl;
            }

            if (current > SMILE_IN_A_ROW)
            {
                cout << "Good Job" << endl;
                break;
            }
        }
        keyboard = waitKey(100);
        i = (i+1) % 10;
    }

    cap.release();
    return 0;
}
