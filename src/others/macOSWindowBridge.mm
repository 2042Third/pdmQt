#import <AppKit/AppKit.h>
#include "macOSWindowBridge.h"

extern "C" void* createNativeMacOSWindow() {
  NSWindow *window = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 480, 300)
                                                 styleMask:NSTitledWindowMask | NSClosableWindowMask | NSResizableWindowMask
                                                   backing:NSBackingStoreBuffered
                                                     defer:NO];
  [window makeKeyAndOrderFront:NSApp];

  // Return the NSView pointer instead of NSWindow
  return (__bridge_retained void*)[window contentView];
}