// before compiling, configure 'Tool' -> 'Memory' -> '1536KB'

#include <Camera.h>

void setup()
{
  Serial.begin(2000000);
  while (!Serial);
  
  // definitions -> https://developer.sony.com/develop/spresense/developer-tools/api-reference/api-references-arduino/Camera_8h.html
  // options     -> https://developer.sony.com/develop/spresense/developer-tools/api-reference/api-references-arduino/group__camera.html
  
  theCamera.begin(2, CAM_VIDEO_FPS_15, CAM_IMGSIZE_VGA_H, CAM_IMGSIZE_VGA_V, CAM_IMAGE_PIX_FMT_JPG);
  
  theCamera.setAutoWhiteBalanceMode(CAM_WHITE_BALANCE_AUTO);
  theCamera.setHDR(CAM_HDR_MODE_AUTO);
  theCamera.setColorEffect(CAM_COLOR_FX_NONE);
  theCamera.setJPEGQuality(50);
  theCamera.setAutoWhiteBalance(true);
  theCamera.setAutoExposure(true);
  theCamera.setAutoISOSensitivity(true);
  
  theCamera.startStreaming(true, CamCB);
}

void loop(){}

void CamCB(CamImage img)
{
  if (img.isAvailable() && wait_char('>', 200)) {
    send_jpeg(img.getImgBuff(), img.getImgSize());
  }
}

void send_jpeg(char* buffer, int size)
{
  Serial.write((size >>  0) & 0xFF);
  Serial.write((size >>  8) & 0xFF);
  Serial.write((size >> 16) & 0xFF);
  Serial.write((size >> 24) & 0xFF);
  int sent = 0;
  while (sent < size)
    sent += Serial.write(&buffer[sent], size - sent);
}

bool wait_char(char code, int timeout)
{
  uint64_t expire = millis() + timeout;
  while (true) {
    if (Serial.available() && Serial.read() == code) 
      return true;
    if (timeout > 0 && millis() > expire) 
      return false;
  }
}
