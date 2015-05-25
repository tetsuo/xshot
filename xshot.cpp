#include <v8.h>
#include <node.h>
#include <nan.h>
#include <CoreVideo/CoreVideo.h>

using namespace node;
using namespace v8;

static CGDirectDisplayID getdisplay (uint32_t n) {
  CGDisplayCount cnt;
  CGDirectDisplayID arr[16];
  CGGetActiveDisplayList(16, arr, &cnt);
  for (uint32_t i = 0; i < cnt; ++ i) {
    if (CGDisplayUnitNumber(arr[i]) == n) {
      return arr[i];
    }
  }
  return kCGNullDirectDisplay;
}

NAN_METHOD (xshot) {
  NanScope();
  
  CGDirectDisplayID display = kCGDirectMainDisplay;

  if (args[0]->IsNumber())
    display = getdisplay(args[0]->Uint32Value());

  if (display == kCGNullDirectDisplay)
    return NanThrowError("display could not be found");

  CFStringRef filetype = kUTTypePNG;

  if (args[1]->IsString() && !strcmp("jpeg", *String::Utf8Value(args[1])))
    filetype = kUTTypeJPEG;

  CGImageRef image = CGDisplayCreateImage(display);

  if (image == NULL)
    return NanThrowError("could not create image");

  CFMutableDataRef data = CFDataCreateMutable(kCFAllocatorDefault, 0);
  CGImageDestinationRef dest = CGImageDestinationCreateWithData(data, filetype, 1, NULL);
  CGImageDestinationAddImage(dest, image, NULL);

  if (!CGImageDestinationFinalize(dest))
    return NanThrowError("could not write");

  CFIndex len = CFDataGetLength(data);
  unsigned char* buf = (unsigned char *) malloc(len);
  CFDataGetBytes (data, CFRangeMake(0, len), buf);

  CFRelease(dest);
  CGImageRelease(image);

  NanReturnValue(NanNewBufferHandle((char *)buf, len));
}

void init (Handle<Object> exports, Handle<Object> module) {
  module->Set(NanNew<String>("exports"), NanNew<FunctionTemplate>(xshot)->GetFunction());
};

NODE_MODULE(xshot, init);