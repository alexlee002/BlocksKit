//
//  NSSet+BlocksKit.h
//  BlocksKit
//

/** Block extensions for NSSet.

 Both inspired by and resembling Smalltalk syntax, these utilities
 allows for iteration of a set in a logical way that
 saves quite a bit of boilerplate code for filtering or finding
 objects or an object.

 Includes code by the following:

- Michael Ash.    <https://github.com/mikeash>.    2010. BSD.
- Corey Floyd.    <https://github.com/coreyfloyd>. 2010.
- Aleks Nesterow. <https://github.com/nesterow>.   2010. BSD.
- Zach Waldowski. <https://github.com/zwaldowski>. 2011. MIT.

 @see NSArray(BlocksKit)
 @see NSDictionary(BlocksKit)
 */
@interface NSSet (BlocksKit)

/** Loops through set and executes the given block with each object.
 
 @param block A single-argument, void-returning code block.
 */
- (void)each:(void (^)(id obj))block;

/** Loops through a set and returns the object matching the block.
 
 @param block A single-argument, BOOL-returning code block.
 @return Returns the object if found, `nil` otherwise.
 @see select:
 */
- (id)match:(BOOL (^)(id obj))block;

/** Loops through a set and returns a set of the objects matching the block.
 
 @param block A single-argument, BOOL-returning code block.
 @return Returns a set of the objects found, `nil` otherwise.
 @see match:
 */
- (NSSet *)select:(BOOL (^)(id obj))block;

/** Loops through a set and returns a set of all objects but the ones matching the block.
 
 This selector performs *literally* the exact same function as select: but in reverse.
 
 This is useful, as one may expect, for removing objects from a set:
     NSSet *new = [reusableWebViews reject:^BOOL(id obj) {
       return ([obj isLoading]);
     }];
 
 @param block A single-argument, BOOL-returning code block.
 @return Returns an array of all objects not found, `nil` if all are excluded.
 */
- (NSSet *)reject:(BOOL (^)(id obj))block;

/** Call the block once for each object and create a set of the return values.
 
 This is sometimes referred to as a transform, mutating one of each object:
 NSSet *new = [mimeTypes map:^id(id obj) {
 return [@"x-dizzytech-" stringByAppendingString:obj]);
 }];
 
 @param block A single-argument, object-returning code block.
 @return Returns a set of the objects returned by the block.
 */
- (NSSet *)map:(id (^)(id obj))block;

/** Arbitrarily accumulate objects using a block.
 
 The concept of this selector is difficult to illustrate in words. The sum can
 be any NSObject, including (but not limited to) an NSString, NSNumber, or NSValue.
 
 You can also do something like summing the count of an item:
 NSNumber *sum = [bodyList reduce:nil withBlock:^id(id sum, id obj) {
 return [NSNumber numberWithInteger: [sum integerValue] + obj.numberOfAppendages];
 }];
 NSUInteger numberOfBodyParts = [sum integerValue];
 
 @param initial The value of the reduction at its start.
 @param block A block that takes the current sum and the next object to return the new sum.
 @return An accumulated value.
 */
- (id)reduce:(id)initial withBlock:(id (^)(id sum, id obj))block;

@end