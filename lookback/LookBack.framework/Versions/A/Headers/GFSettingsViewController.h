//
//  GFSettingsViewController.h
//  LookBack
//
//  Created by Joachim Bengtsson on 2012-10-11.
//  Copyright (c) 2012 ThirdCog. All rights reserved.
//

#import <UIKit/UIKit.h>
@class LookBack;

@interface GFSettingsViewController : UITableViewController
// Loads a new SettingsVC from the .storyboard. Don't instantiate this class directly. Push result onto a navigation controller.
+ (id)settingsViewControllerForInstance:(LookBack*)gf;
@end
