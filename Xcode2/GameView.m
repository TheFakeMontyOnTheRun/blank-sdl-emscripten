//
//  GameView.m
//  The Mistral Report
//
//  Created by Daniel Monteiro on 10/13/18.
//  Copyright (c) 2018 Daniel Monteiro. All rights reserved.
//
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


#import "GameView.h"

#include "Common.h"
#include "Enums.h"
#include "Globals.h"
#include "FixP.h"
#include "LoadBitmap.h"
#include "Engine.h"
#include "CRenderer.h"

extern         GameView* osxview;

@implementation GameView

uint32_t stretchedBuffer[ 320 * 200 ];
CGColorSpaceRef rgb;
CGDataProviderRef provider;
CGImageRef ref;
NSMutableSet* playingSounds;

int nextAudioChannel = -1;
float multiplier = 1.0f;

//NSString* fileNamesForSounds[] = {@"menu_move", @"menu_select", @"gotclue", @"detected2", @"bong", @"fire", @"enemyfire", @"derelicttheme"};

//NSSound* playerSounds[8];

id delegate;

void setupOPL2(int port) {
//    int c;
//    NSBundle *bundle = [NSBundle mainBundle];
//    playingSounds = [[NSMutableSet alloc] init];
//
//    for ( c = 0; c < 8; ++c ) {
//        NSString* path = [[NSURL fileURLWithPath: [ bundle pathForResource: fileNamesForSounds[c] ofType:@"wav"]] path ];
//        playerSounds[c] = [[NSSound alloc] initWithContentsOfFile: path byReference: NO];
//        [playerSounds[c] setDelegate: delegate ];
//    }
}


void stopSounds() {
//    int count = [playingSounds count];
//    int c = 0;
//    NSArray* groupsArray = [playingSounds allObjects];
//    for (c = 0; c < count; ++c ) {
//        NSSound* sound = [groupsArray objectAtIndex: c ];
//        [sound stop];
//    }
}

void playSound( const int action ){
//    NSSound *original = playerSounds[action];
//    NSSound *newSound =  (NSSound*)[original copy ];
//    [playingSounds addObject: newSound ];
//    [newSound play];
}

- (void)sound:(NSSound *)sound didFinishPlaying:(BOOL)aBool {
//    [sound release];
//    [playingSounds removeObject: sound ];
}

void soundTick() {}

void muteSound() {}


- (void) repaintGame:(NSTimer *)timer
{
    isRunning = menuTick(50);
    
    if (!isRunning) {
        exit(0);
    }
    
    [self setNeedsDisplay: YES ];
}

void setMultiplier(CGSize size) {
    
    if (((320.0f / 240.0f ) * size.height) < size.width ) {
        multiplier = (((float)size.height) / 240.0f);
    } else {
        multiplier = (((float)size.width) / 320.0f);
    }
}

- (id)initWithFrame:(NSRect)frame
{
    int r, g, b;
    
    self = [super initWithFrame:frame];
    if (self) {
        
        bufferedInput = -1;
        buffer = NULL;
        delegate = self;
        rgb = CGColorSpaceCreateDeviceRGB();
        
        for (r = 0; r < 256; r += 16) {
            for (g = 0; g < 256; g += 8) {
                for (b = 0; b < 256; b += 8) {
                    uint32_t pixel = 0xFF000000 + (r << 16) + (g << 8) + (b);
                    uint8_t paletteEntry = getPaletteEntry(pixel);
                    uint32_t newPixel;
                    
                    
#ifndef __BIG_ENDIAN_
                    newPixel = (((pixel & 0x000000FF) - 0x38) << 24) +
                    ((((pixel & 0x0000FF00) >> 8) - 0x18) << 16) +
                    ((((pixel & 0x00FF0000) >> 16) - 0x10) << 8 );
#else
                    newPixel = (((pixel & 0x000000FF) - 0x38 ) << 8) +
                    ((((pixel & 0x0000FF00) >> 8) - 0x18) << 16) +
                    ((((pixel & 0x00FF0000) >> 16) -0x10) << 24 );
                    
#endif
                    
                    palette[paletteEntry] = newPixel;
                }
            }
        }
        
        osxview = self;
        
        srand(time(NULL));
        
        initHW();
        enterState(kMainMenu);
        
        menuTick(50);
        [self initTimer];
    }
    
    return self;
}

-(void)keyDown:(NSEvent *)theEvent
{
}

-(void)keyUp:(NSEvent*)event
{
    
    bufferedInput = [ event keyCode ];
}

- (BOOL)acceptsFirstResponder {
    return YES;
}

- (void)setBuffer:(uint8_t*) bufferFromOutside {
    buffer = bufferFromOutside;
}


-(void) initTimer {
    [NSTimer scheduledTimerWithTimeInterval:0.05f
                                     target:self selector:@selector(repaintGame:) userInfo:nil repeats:YES];
    
}

- (int) getInput {
    int toReturn = bufferedInput;
    
    bufferedInput = -1;
    
    return toReturn;
}

-(void) stopTimer {
}

void shutdownHW() {
    CGColorSpaceRelease(rgb);
}


- (void)drawRect:(NSRect)rect {
    int x,y;
    CGRect bounds;
    //NSRectToCGRect is not available on 10.4
    bounds.origin.x = rect.origin.x;
    bounds.origin.y = rect.origin.y;
    bounds.size.width = rect.size.width;
    bounds.size.height = rect.size.height;
    
    float yMultiplier = ( (240.0f * multiplier) / 200.0f );
    
    if (buffer == NULL ){
        return;
    }
    
    setMultiplier(bounds.size);
    

    uint8_t *pixelPtr = &buffer[0];
    uint32_t *bufferPtr = &stretchedBuffer[0];
    for ( y = 0; y < 200; ++y ) {
        for ( x = 0; x < 320; ++x ) {
            uint8_t index = *pixelPtr;
            uint32_t pixel = palette[ index ];
            *bufferPtr = pixel;
            ++pixelPtr;
            ++bufferPtr;
        }
    }
    
        
        
        
    /*  MAC_OS_X_VERSION_10_10*/
#if MAC_OS_X_VERSION_MIN_REQUIRED >= 101000
    CGContextRef context = (CGContextRef)[[NSGraphicsContext currentContext] CGContext];
#else
    CGContextRef context = (CGContextRef)[[NSGraphicsContext currentContext] graphicsPort];
#endif
    
    CGContextSaveGState(context);
    
    CGContextSetRGBFillColor(context, 0.0f, 0.0f, 0.0f, 1.0f);
    CGContextFillRect(context, bounds);
    
    provider = CGDataProviderCreateWithData( NULL, &stretchedBuffer[0], 4 * 320 * 200, NULL );
    ref = CGImageCreate( 320, 200, 8, 32, 4 * 320, rgb, kCGBitmapByteOrder32Host, provider, NULL, 0, kCGRenderingIntentDefault );
    CGContextScaleCTM(context, multiplier, yMultiplier);
    CGContextDrawImage(context, CGRectMake( ((bounds.size.width / multiplier) - 320) / 2, ((bounds.size.height / yMultiplier) - 200) / 2, 320, 200), ref);
    CGImageRelease(ref);
    CGDataProviderRelease(provider);
    
    CGContextRestoreGState(context);
}
@end
