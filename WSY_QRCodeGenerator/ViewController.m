//
//  ViewController.m
//  WSY_QRCodeGenerator
//
//  Created by Andou on 14/12/9.
//  Copyright (c) 2014年 SCDev. All rights reserved.
//

#import "ViewController.h"
#import "DataMatrix.h"
#import "QREncoder.h"
@interface ViewController ()
@property (weak, nonatomic) IBOutlet UIImageView *qrImage;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    DataMatrix* qrMatrix = [QREncoder encodeWithECLevel:QR_ECLEVEL_AUTO version:QR_VERSION_AUTO string:@"http://stackoverflow.com/questions/9633355/most-efficient-way-to-copy-a-file-with-gcd"];
    self.qrImage.image = [QREncoder renderDataMatrix:qrMatrix imageDimension:200];
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
