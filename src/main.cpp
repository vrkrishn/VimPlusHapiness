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

    int SMILE_IN_A_ROW = 3;
    int current = 0;

    const char * thoughts[] = {"What a great coder", "I'm sure that will work", "What a boss", "Thats Amazing", "With code like that, who needs the rest of the team", "Isn't this code great"};
    srand(time(NULL));
    int index = rand() % 7;
    cout << "GET READY FOR THE GOOD FEELS!!!" << endl;
    cout << thoughts[index] << endl;

    cout << "SMILE for " << SMILE_IN_A_ROW << " seconds" << endl;


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

        ellipse(frame, Point(frame.rows/2, frame.cols/3), Size(2*frame.rows/3, frame.cols/4),0.0, 0.0, 0.0, Scalar(0,255,255), 2);
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
                cout << "You frowned start over" << endl;
                current = 0;
            }

            if (current > SMILE_IN_A_ROW)
            {
                break;
            }
        }
        keyboard = waitKey(100);
        i = (i+1) % 10;
    }

    cap.release();
    return 0;
}
