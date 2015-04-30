#include "cv.h"
#include "Windows.h"
#include "highgui.h"
#include "math.h"
 
int main()
{
    int ME=0x8001;
    int x=0,y=0;
    long counter=0;
     
    IplImage* gray;
    IplImage* cannyImg;
 
    CvMemStorage* storage = cvCreateMemStorage(0);
 
    CvCapture *capture = 0;
    IplImage  *src = 0;
    int key = 0;
    int threshold = 120, maxValue = 255;
    int thresholdType = CV_THRESH_BINARY;
  
 
    /* initialize camera */
    capture = cvCaptureFromCAM( 0 );
  
    /* always check */
    if ( !capture )
    {
        fprintf( stderr, "Cannot open initialize webcam!\n" );
        return 1;
    }
 
    cvSetCaptureProperty(capture,CV_CAP_PROP_FRAME_WIDTH,320);
    cvSetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT,240);
 
    /* create a window for the video */
    cvNamedWindow( "camera", CV_WINDOW_AUTOSIZE );
  
    while( key != 'q' ) 
    {
         
                 counter+=1;
                 if(counter==55)
                 {
                    mouse_event(0x0002,0,0,0,0);
                    mouse_event(0x0004,0,0,0,0);
                    counter=0;
                 }
 
              
              
             
         
        /* get a frame */
        src = cvQueryFrame( capture );
         
        /* draw grid*/
        cvLine(src, cvPoint(105,0), cvPoint(105,240), cvScalar(0,255,0), 1);    
        cvLine(src, cvPoint(210,0), cvPoint(210,240), cvScalar(0,255,0), 1);
        cvLine(src, cvPoint(0,80), cvPoint(320,80), cvScalar(0,255,0), 1);
        cvLine(src, cvPoint(0,160), cvPoint(320,160), cvScalar(0,255,0), 1);
  
        /* always check */
        if( !src ) break;
        
        /* display current frame */
         
        cvShowImage( "camera", src );
         
        gray = cvCreateImage( cvSize(src->width, src->height), IPL_DEPTH_8U, 1 );
         
        cvCvtColor( src, gray, CV_BGR2GRAY );
         
        cvSmooth( gray, gray, CV_GAUSSIAN, 9, 9 );
         
        cannyImg = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
         
        /* edge detection using canny */
        cvCanny(gray, cannyImg, 50, 150, 3);
      
        /* circle detection using hough algorithm */
        CvSeq* circles = cvHoughCircles( gray, storage, CV_HOUGH_GRADIENT, 2, gray->height/4, 200, 100,0,0);
         
        int i=0;        
        for( i = 0; i < circles->total; i++ )
        {
             float* p = (float*)cvGetSeqElem( circles, i );
             circles->total=0;
              
             /* draw dot @ centre of the circle */
             cvCircle( src, cvPoint(cvRound(p[0]),cvRound(p[1])), 3, CV_RGB(0,255,0), -1, 8, 0 );
              
             /* draw a circle */
             cvCircle( src, cvPoint(cvRound(p[0]),cvRound(p[1])), cvRound(p[2]), CV_RGB(255,0,0), 3, 8, 0 );
              
             x=cvRound(p[0]);
             y=cvRound(p[1]);
             printf("\nX=%d   \tY=%d  \tRadius=%d",x,y,cvRound(p[2]));
             
            if(x>=188 && x<=200)
                {
                    mouse_event(ME,15000,27600,0,0);
                }   
            if(x<=165 && x<=180 && y >=58 && y<=71)
                {
                    mouse_event(ME,28000,27600,0,0);
                }
            if(x>=0 && x<=150 && y>=58 && y<=71)
                {
                    mouse_event(ME,42000,27600,0,0);
                }
                 
            if(y>=0 && y<=40)
                {
                    mouse_event(ME,28000,15600,0,0);
                }
            if(y>=78 && y<=90)
                {
                    mouse_event(ME,28000,39600,0,0);
                }
                 
         
        }
     
        cvNamedWindow( "circles", 1 );cvShowImage( "circles", src );
         
        cvReleaseImage( &gray );
        cvReleaseImage( &cannyImg );
 
         
 
        /* exit if user press 'q' */
        key = cvWaitKey( 1 );
    }
  
    cvDestroyWindow( "camera" );
    cvReleaseCapture( &capture );
 
return 0;
}
