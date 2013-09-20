Lookback.io
===========

Lookback is a tool and library for user experience testing that you can integrate into your app. Lookback records the iOS screen, the front-facing camera, microphone, metadata, touches and active views, and uploads it all in near-realtime to lookback.io where you can study and dive into the data.

Some use cases are:

* User testing sessions. Instead of mounting web cams in your testing lab to record both the screen and your tester's reactions, let Lookback do the hard work for you.
* Long-term usability study. Let a user record a week of using your app, and study trends, reactions and recurring problems.
* Quality assurance. Record videos of found bugs, complete with a trace of how the tester reached it.


## Integration

### Getting Lookback into your app

First off, you'll need to register and sign in to lookback.io. Once signed in, [download the latest version of libLookback](http://lookback.io/download), and follow these instructions:

1. Unpack "lookback.zip" into your project folder <br /> <img src="http://f.cl.ly/items/0e3i3L3O3x3C09052J1r/step1.png" width="430"/>

2. Pull LookBack.framework and LookBack-Resources into your project (for example, into the Frameworks folder). In the dialog box, don't copy items into destination group's folder, and do choose to create groups for any added folders (instead of folder references). Make sure that your main app target is selected.<br /><img src="http://f.cl.ly/items/2W1p3g3p2I41183G1P2S/step2.png" width="572" /><br /> <img src="http://f.cl.ly/items/1n3e1m2F2E0q3k0i1j33/step2-2.png" width="728" />
3. You need to add "-ObjC" to your linker flags. Select your project in the sidebar, then your main target, then Build Settings. Search for "Other Linker Flags", and append "-ObjC". <br /> <img src="http://f.cl.ly/items/2v1k1g0x2f2M2V421f3J/step3.png" width="1075" />
4. Lookback uses a number of system frameworks that you have to link your app to. In addition, you need to link with libLookBack.a. In the same view, click "Build Phases", then "Link Binary With Libraries", and then the "+" button to add the following frameworks:
   * AVFoundation.framework
   * AudioToolbox.framework   
   * CoreVideo.framework
   * CoreMedia.framework
   * MediaPlayer.framework
   * QuartzCore.framework
   * SystemConfiguration.framework
   * LookBack.framework
   <br /> <img src="http://f.cl.ly/items/2I1y2g1r1q0Q2T2A393e/step4.png" width="791" />
5. Before you can add LookBack to your app, you need to [register your app at lookback.io](http://lookback.io/app/). Press the "+" button in the sidebar, and fill in the details for your app. <br /> ![Step 5.1](http://f.cl.ly/items/2m3K0a1r1B1l0S0U370C/Screen%20Shot%202013-06-03%20at%206.26.00%20PM.png) <br /> ![Step 5.2](http://f.cl.ly/items/102v1K3j0R47120R1W1x/Screen%20Shot%202013-06-03%20at%206.26.06%20PM.png)
6. Click the "Settings" button for your app. You'll be presented with a "Token". You'll need it soon: copy it. <br > ![Step 6](http://f.cl.ly/items/3D3H0D1211323x160019/step%206.png)
7. It's time to start Lookback up. You need to setup the LookBack class with the app token you just copied. You'll also want a way to start a recording, for example by pressing a button. It could look something like this:

// SRAppDelegate.m

	#import <LookBack/LookBack.h>
	
	@interface SRAppDelegate ()
	@property(nonatomic) LookBack *lookBack;
	@end
	
	@implementation SRAppDelegate
	
	- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
	{
	    .......
	    [LookBack setupWithAppToken:@"4zzH5Rblurblurblur"];
	    
	    UIButton *lookbackSettingsButton = [UIButton buttonWithType:UIButtonTypeInfoLight];
	    lookbackSettingsButton.frame = CGRectMake(300, 10, 10, 10);
	    [lookbackSettingsButton addTarget:self action:@selector(showLookbackSettings:) forControlEvents:UIControlEventTouchUpInside];
	    [self.window addSubview:lookbackSettingsButton];
	    .......
	}

	- (IBAction)showLookbackSettings:(id)sender
	{
	    UIViewController *vc = [GFSettingsViewController settingsViewControllerForInstance:[LookBack lookback]];
	    [self.navigationController pushViewController:vc animated:YES];
	}

This will get you started with screen, touches, camera and microphone recording. For additional features, read on.


### Tagging views while recording

Lookback can tag segments of your recording with the view that the user is visiting. You can then later filter your list of recordings on which views the user visited. Note that these should be names that identify that type of view, so for a profile view, you should log "Profile", not "Nevyn's Profile", otherwise you won't be able to filter on that view type on the web site later.

If you implement the method `+(NSString*)lookBackIdentifier` in your view controller, that view will automatically be logged under that name. Otherwise, your view controller's class name will be used instead, with prefix ("UI") and suffix ("ViewController") removed.

You can disable this behavior by setting the user default `GFAutomaticallyLogViewAppearance` to NO, and calling `-[LookBack enteredView:]` and `-[LookBack exitedView:]` methods manually.

Example of the two types of manual logging

	// Just provide a name
	+ (NSString*)lookBackIdentifier
	{
	    return @"Menu";
	}
	
	// OR: explicitly call entered/exited methods.
	
	- (void)applicationDidFinishLaunching
	{
	    ...
	    [[NSUserDefaults standardUserDefaults] setBool:NO forKey:GFAutomaticallyLogViewAppearance]
	}
	
	- (void)viewDidAppear:(BOOL)animated
	{
	    [super viewDidAppear:animated];
	    [_lookback enteredView:@"Menu"];
	}
	- (void)viewWillDisappear:(BOOL)animated
	{
	    [super viewWillDisappear:animated];
	    [_lookback exitedView:@"Menu"];
	}

Settings
--------

### The "Upload when inactive" option

Normally when you start a recording, it will be paused whenever the application becomes inactive (backgrounded or screen locked). If you record a very long session, it will take a long time to upload, and be difficult to manage. In this case, you might want to enable the "Upload when inactive" option. Then, recording will stop when the app is inactive, the short session uploaded, and a new recording started anew when the app becomes active.


