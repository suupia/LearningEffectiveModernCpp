#ifdef __APPLE__

#import <Cocoa/Cocoa.h>

int run_platform_app() {
  @autoreleasepool {
    [NSApplication sharedApplication];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

    NSRect frame = NSMakeRect(0, 0, 640, 360);
    NSUInteger style = NSWindowStyleMaskTitled |
                       NSWindowStyleMaskClosable |
                       NSWindowStyleMaskMiniaturizable |
                       NSWindowStyleMaskResizable;

    NSWindow* window = [[NSWindow alloc] initWithContentRect:frame
                                                   styleMask:style
                                                     backing:NSBackingStoreBuffered
                                                       defer:NO];
    [window setTitle:@"Hello Window"];
    [window center];

    NSTextField* label = [[NSTextField alloc] initWithFrame:NSMakeRect(0, 0, 200, 40)];
    [label setStringValue:@"Hello World"];
    [label setBezeled:NO];
    [label setDrawsBackground:NO];
    [label setEditable:NO];
    [label setSelectable:NO];
    [label setFont:[NSFont systemFontOfSize:32 weight:NSFontWeightRegular]];
    [label sizeToFit];

    NSView* content = [window contentView];
    NSRect bounds = [content bounds];
    NSRect labelFrame = [label frame];
    labelFrame.origin.x = (NSWidth(bounds) - NSWidth(labelFrame)) * 0.5;
    labelFrame.origin.y = (NSHeight(bounds) - NSHeight(labelFrame)) * 0.5;
    [label setFrame:labelFrame];
    [label setAutoresizingMask:NSViewMinXMargin | NSViewMaxXMargin |
                                 NSViewMinYMargin | NSViewMaxYMargin];

    [content addSubview:label];
    [window makeKeyAndOrderFront:nil];

    [NSApp activateIgnoringOtherApps:YES];
    [NSApp run];
  }

  return 0;
}

#endif
