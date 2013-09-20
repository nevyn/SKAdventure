#import <Foundation/Foundation.h>
#import <LookBack/GFSettingsViewController.h>

/** Public interface for Lookback.io, the UX testing tool. */
@interface LookBack : NSObject
/** In your applicationDidFinishLaunching: or similar, call this method to prepare
    Lookback for use, using the App Token from your integration guide at lookback.io.
*/
+ (void)setupWithAppToken:(NSString*)appToken;

/** Shared instance of LookBack to use from your code. You must call
    +[LookBack setupWithAppToken:] before calling this method. */
+ (LookBack*)lookback;

/// Whether Lookback is set to recording. You can either set this programmatically,
/// or use GFSettingsViewController to let the user activate it.
@property(nonatomic) BOOL enabled;

/** Is Lookback paused? Lookback will pause automatically when app is inactive.
    The value of this property is undefined if recording is not enabled (as there
    is nothing to pause) */
@property(nonatomic,getter=isPaused) BOOL paused;

/** Identifier for the user who's currently using the app. You can filter on
    this property at lookback.io later. If your service has log in user names,
    you can use that here. (optional) */
@property(nonatomic,copy) NSString *userIdentifier;

/** Track user navigation. Optional, and automatic if you don't use these methods
    manually. See README for more details.
    @param viewIdentifier Unique human readable identifier for a specific view
*/
- (void)enteredView:(NSString*)viewIdentifier;
- (void)exitedView:(NSString*)viewIdentifier;

// For debugging
@property(nonatomic,readonly) NSString *appToken;
@end

#pragma mark Settings

/** If you implement the method `+(NSString*)lookBackIdentifier` in your view controller, that view will automatically be logged under that name (and later filter on it at lookback.io). Otherwise, your view controller's class name will be used instead, with prefix ("UI") and suffix ("ViewController") removed. You can disable this behavior by setting the user default `GFAutomaticallyLogViewAppearance` to NO, and calling `-[LookBack enteredView:]` and `-[LookBack exitedView:]` methods manually.*/
extern NSString *const GFAutomaticallyLogViewAppearance;

/** Normally when you start a recording, it will be paused whenever the application becomes inactive (backgrounded or screen locked). If you record a very long session, it will take a long time to upload, and be difficult to manage. In this case, you might want to enable the "Upload when inactive" option in Settings (or the GFAutosplitSettingsKey BOOL default). Then, recording will stop when the app is inactive, the short session uploaded, and a new recording started anew when the app becomes active.*/
extern NSString *const GFAutosplitSettingsKey;

/** The BOOL default GFCameraEnabledSettingsKey controls whether the front-facing camera will record, in addition to recording the screen. */
extern NSString *const GFCameraEnabledSettingsKey;

/** The BOOL default GFAudioEnabledSettingsKey controls whether audio will be recorded together with the front-facing camera. Does nothing if GFCameraEnabledSettingsKey is NO. */
extern NSString *const GFAudioEnabledSettingsKey;

/** The BOOL default GFShowPreviewSettingsKey controls whether the user should be shown a preview image of their face at the bottom-right of the screen while recording, to make sure that they are holding their iPhone correctly and are well-framed. */
extern NSString *const GFShowPreviewSettingsKey;
