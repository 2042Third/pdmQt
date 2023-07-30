#include <AppKit/AppKit.h>

extern "C" void* createNativeMacOSWindow() {
  // Create a new window
  NSWindow *window = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 480, 300)
                                                 styleMask:NSTitledWindowMask | NSClosableWindowMask | NSResizableWindowMask
                                                   backing:NSBackingStoreBuffered
                                                     defer:NO];

  // Create a new title bar view
  NSView *titleBarView = [[NSView alloc] initWithFrame:NSMakeRect(0, 0, window.frame.size.width, window.frame.size.height)];

  // Create a button
  NSButton *button = [NSButton buttonWithTitle:@"Button" target:nil action:nil];

  // Set the button's frame
  button.frame = NSMakeRect(titleBarView.frame.size.width/2 - button.frame.size.width/2, 0, button.frame.size.width, button.frame.size.height);

  // Add the button to the title bar view
  [titleBarView addSubview:button];

  // Set the window's title bar view
  window.titlebarAppearsTransparent = YES;
  window.titleVisibility = NSWindowTitleHidden;
  window.styleMask |= NSWindowStyleMaskFullSizeContentView;

  // Add the custom title bar view to the window's content view
  [window.contentView addSubview:titleBarView];

  // Show the window
  [window makeKeyAndOrderFront:NSApp];

  return (__bridge void *)[window windowNumber];
}