#include <Kinect.h>
#include <kinect.visualgesturebuilder.h>
#include <windows.h>
#include <iostream>

int frameHandler(IVisualGestureBuilderFrameReader* reader, IGesture* gestureList, int num_gestures) {
    IVisualGestureBuilderFrame *gestureFrame = nullptr;
    if(reader->CalculateAndAcquireLatestFrame(&gestureFrame) < 0) {
        std::wcerr << L"Reader couldn't acquire latest frame\n";
        return -1;
    }

    int whichGestureIndex = -1;
    IDiscreteGestureResult *result;
    for(int i = 0; i < num_gestures; i++) {
        if(gestureFrame->get_DiscreteGestureResult(&gestureList[i], &result) < 0) {
            std::wcerr << L"Failed to read out gestures result from frame\n";
            return -1;
        }
        BOOLEAN detected = 0;
        float confidence = 0.0;
        if(result->get_Detected(&detected) < 0) {
            std::wcerr << L"Failed to get gesture detection indicator\n";
            return -1;
        }
        if(result->get_Confidence(&confidence) < 0) {
            std::wcerr << L"Failed to get gesture confidence indicator\n";
            return -1;
        }
        if (detected == TRUE && confidence >= 0.8) {
            whichGestureIndex = i;
            break;
        }
    }

    switch (whichGestureIndex) {
    case 0:
        wprintf(L"Gesture 0 detected with high confidence\n");
        break;
    default:
        break;
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    //Simply opens the Kinect device. The first thing we need to do before we can do anything.
    IKinectSensor* kinect = nullptr;
    HRESULT hr = GetDefaultKinectSensor(&kinect);
    if (hr < 0) {
        std::wcerr << L"GetDefaultKinectSensor failed\n";
        return -1;
    }
    hr = kinect->Open();
    if (hr < 0) {
        std::wcerr << L"Opening kinect sensor failed\n";
        return -1;
    }

    //Opens the gesture database 
    IVisualGestureBuilderDatabase* vgbDB = nullptr;
    const wchar_t* databasePath = L"test_project.gbd";
    /* For some reason windows C++ programs seem to always return sucess or failure
    as a HRESULT type. HRESULT is actually just a normal integer where hr < 0 means
    the function failed for some reason and hr >= 0 indicates success. */
    hr = CreateVisualGestureBuilderDatabaseInstanceFromFile(databasePath, &vgbDB);
    if (hr < 0) {
        std::wcerr << L"CreateVisualGestureBuilderDatabaseInstanceFromFile failed\n";
        return -1;
    }
    wprintf(L"Succesfully opened the VGB Database\n");

    //Creates a frame source. I think this is bascially creates an input through 
    //which the Kinect can feed it's camera data into the program
    IVisualGestureBuilderFrameSource* vgbFrameSource = nullptr;
    hr = CreateVisualGestureBuilderFrameSource(kinect, 0, &vgbFrameSource);
    if (hr < 0) {
        std::wcerr << L"CreateVisualGestureBuilderFrameSource failed\n";
        return -1;
    }

    /* Creates a frame reader, which collects frames from the frame source. 
    The latest frames can then be inspected individually by using:argc
    vgbFrameReader->AcquireFrame(IVisualGestureBuilderFrame **gestureFrame)
    The gestureFrame can then be queried for whether a gesture is being performed
    in that frame. */
    IVisualGestureBuilderFrameReader* vgbFrameReader = nullptr;
    hr = vgbFrameSource->OpenReader(&vgbFrameReader);
    if (hr < 0) {
        std::wcerr << L"Opening VGB Frame Reader failed\n";
        return -1;
    }

    /* vgbFrameSource needs to be told which gestures to look out for. The gestures
    from vgbDB need to be added one by one first. */
    UINT count = 0;
    IGesture* gestureList;
    hr = vgbDB->get_AvailableGesturesCount(&count);
    if (hr < 0) {
        std::wcerr << L"Couldn't get gesture count\n";
        return -1;
    }
    hr = vgbDB->get_AvailableGestures(count, &gestureList);
    if (hr < 0) {
        std::wcerr << L"Couldn't get list of gestures\n";
        return -1;
    }
    wprintf(L"Count is %d\n", count);
    for (UINT i = 0; i < count; ++i) {
        wprintf(L"test1\n");
        hr = vgbFrameSource->AddGesture(&gestureList[i]);
        wprintf(L"test2\n");
        if (hr < 0) {
            std::wcerr << L"Adding gesture fro VGB Frame Soucre failed\n";
            return -1;
        } else {
            wprintf(L"Succesfully added a gesture\n");
        }
        wprintf(L"test3\n");
    }

    while(1) {
        if (frameHandler(vgbFrameReader, gestureList, count) <= 0) {
            return -1;
        }
    }
    wprintf(L"vgbFrameReader has been created and gestures have been added. Test successful, shutting down program\n");
    return 0;
}
