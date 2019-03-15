from picamera import PiCamera
from time import sleep

camera = PiCamera()

# Length of video capture in seconds.
video_length = 10

# Approximately how long (in seconds) to wait in between captures.
interval_length = 1000

# Take video recordings and still image captures.
for iteration in range(1, 101):

    # Video recording.
    camera.start_preview()
    sleep(2)
    camera.start_recording('/home/pi/video' + str(iteration) + '.h264')
    sleep(video_length)
    camera.stop_recording()
    camera.stop_preview()

    # Still image capture.
    camera.start_preview()
    sleep(2)
    camera.start_recording('/home/pi/img' + str(iteration) + '.jpg')
    camera.stop_recording()
    camera.stop_preview()

    # Wait for interval.
    sleep(interval_length)
