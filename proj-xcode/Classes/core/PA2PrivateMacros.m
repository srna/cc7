/**
 * Copyright 2016 Wultra s.r.o.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import "PA2PrivateMacros.h"
#import "PA2ErrorConstants.h"

id PA2CastToImpl(id instance, Class desiredClass)
{
	if ([instance isKindOfClass:desiredClass]) {
		return instance;
	}
	return nil;
}

NSError * PA2MakeError(NSInteger errorCode, NSString * message)
{
	NSDictionary * info = message ? @{ NSLocalizedDescriptionKey: message} : nil;
	return [NSError errorWithDomain:PA2ErrorDomain code:errorCode userInfo:info];
}