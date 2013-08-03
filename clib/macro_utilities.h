#ifndef __MACRO_UTILITIES_H__
#define __MACRO_UTILITIES_H__

/** File: macro_utilities.h
	Author: Ben Nye
	Description: Generic Macro Utilities for Dealing with Macro Functions

	Licensing (APL V2.0)
	---------------------------------------------
    Copyright 2011 Benjamin D. Nye

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
	
       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
   ---------------------------------------------
   
   Notes: 
	- Some code here was taken from the Public Domain.  In all cases of such,
	  the original author is noted as well as the original source.
	- All macros listed here are rated up to at least 64 arguments.  If you need more,
	  feel free to make more.
	- If you are making them, I recommend generating them with a scripting language.  Beats
	  copy and paste, any day.  These enumerated macros were generated using Python.
	-  Being CPP macros, these will not fail elegantly.  The most common cause of failures
	   will result from an incorrect # of arguments or attempting to nest macros (not all of these
	   play nicely with nesting, due to how the variadic counting works).
*/

/* Simple Macros */
#define MAKE_COMMA() MAKE_COMMA1()
#define MAKE_COMMA1() MAKE_COMMA2()
#define MAKE_COMMA2() ,

/** STRINGIZE and CONCATENATE from Gregory Pakosz
	Source: http://stackoverflow.com/questions/1872220/is-it-possible-to-iterate-over-arguments-in-variadic-macros
*/
#define STRINGIZE(arg)  STRINGIZE1(arg)
#define STRINGIZE1(arg) STRINGIZE2(arg)
#define STRINGIZE2(arg) #arg

#define CONCATENATE(arg1, arg2)   CONCATENATE1(arg1, arg2)
#define CONCATENATE1(arg1, arg2)  CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2)  arg1##arg2

/* 	---------------------------------
	|    Variadic/Iteration Macros   | 
	---------------------------------*/
	
/*****************************************************
 COUNT_ARGUMENTS Counts the number of args to a variadic function, up to 64 (renamed from PP_NARG)
 Description: P_NARG macro returns the number of arguments that have been passed to it.
 Author: Laurent Deniau
 Source: https://groups.google.com/group/comp.std.c/browse_thread/thread/77ee8c8f92e4a3fb?hl=en%29
 NOTE: This may not work reliably if the function receives zero args, depending on compiler
*******************************************************/

#define COUNT_ARGUMENTS(...) PP_NARG_(,##__VA_ARGS__,PP_RSEQ_N())
#define PP_NARG_(...) PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N( \
         _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N
#define PP_RSEQ_N() \
         63,62,61,60,                   \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0


/*****************************************************
 FOR_EACH_COMPOSER Composition macro to create expressions where some sequence is bound by prefix <element> postfix
 Description: For each macro, but built more generally to allow expressing sums as well as series of functions.
 Adapted from: Gregory Pakosz and Chris Dodd (StackExchange)
   Sources: http://stackoverflow.com/questions/1872220/is-it-possible-to-iterate-over-arguments-in-variadic-macros, 
			http://stackoverflow.com/questions/6218946/c-function-that-calculates-total-sizeof-arguments
 Functional up to 64 arguments.
*******************************************************/
#define FOR_EACH_COMPOSER_0(prefix, postfix, finalPrefix, finalPostfix, ...)
#define FOR_EACH_COMPOSER_1(prefix, postfix, finalPrefix, finalPostfix, x, ...) finalPrefix(x)finalPostfix
#define FOR_EACH_COMPOSER_2(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_1(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_3(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_2(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_4(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_3(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_5(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_4(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_6(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_5(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_7(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_6(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_8(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_7(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_9(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_8(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_10(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_9(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_11(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_10(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_12(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_11(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_13(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_12(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_14(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_13(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_15(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_14(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_16(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_15(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_17(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_16(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_18(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_17(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_19(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_18(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_20(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_19(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_21(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_20(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_22(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_21(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_23(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_22(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_24(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_23(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_25(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_24(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_26(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_25(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_27(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_26(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_28(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_27(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_29(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_28(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_30(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_29(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_31(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_30(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_32(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_31(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_33(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_32(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_34(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_33(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_35(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_34(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_36(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_35(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_37(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_36(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_38(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_37(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_39(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_38(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_40(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_39(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_41(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_40(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_42(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_41(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_43(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_42(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_44(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_43(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_45(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_44(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_46(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_45(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_47(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_46(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_48(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_47(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_49(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_48(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_50(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_49(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_51(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_50(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_52(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_51(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_53(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_52(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_54(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_53(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_55(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_54(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_56(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_55(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_57(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_56(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_58(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_57(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_59(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_58(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_60(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_59(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_61(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_60(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_62(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_61(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_63(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_62(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER_64(prefix, postfix, finalPrefix, finalPostfix, x, ...)\
  prefix(x)postfix\
  FOR_EACH_COMPOSER_63(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)

#define FOR_EACH_COMPOSER_(N, prefix, postfix, finalPrefix, finalPostfix, ...) CONCATENATE(FOR_EACH_COMPOSER_, N)(prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
#define FOR_EACH_COMPOSER(prefix, postfix, finalPrefix, finalPostfix, ...) FOR_EACH_COMPOSER_(COUNT_ARGUMENTS(__VA_ARGS__), prefix, postfix, finalPrefix, finalPostfix, __VA_ARGS__)
  
/*****************************************************
 SIZE_OF_ARGUMENTS Calculates the size of the given arguments
 Description: For each argument, calculates the sizeof returns the sum
 Author: Benjamin Nye
 NOTE: This may not work reliably if the function receives zero args, depending on compiler
*******************************************************/
#define SIZE_OF_ARGS(...) FOR_EACH_COMPOSER_(COUNT_ARGUMENTS(__VA_ARGS__), sizeof, +, sizeof, +, __VA_ARGS__) 0

	
/******************************************************
   FOR_EACH Macro
   Adapted from: Gregory Pakosz and Chris Dodd (StackExchange)
   Sources: http://stackoverflow.com/questions/1872220/is-it-possible-to-iterate-over-arguments-in-variadic-macros, 
			http://stackoverflow.com/questions/6218946/c-function-that-calculates-total-sizeof-arguments
   Functional up to 64 arguments.
*******************************************************/
#define FOR_EACH_0(what, x, ...)
#define FOR_EACH_1(what, x, ...) what(x)
#define FOR_EACH_2(what, x, ...)\
  what(x);\
  FOR_EACH_1(what,  __VA_ARGS__)
#define FOR_EACH_3(what, x, ...)\
  what(x);\
  FOR_EACH_2(what, __VA_ARGS__);
#define FOR_EACH_4(what, x, ...)\
  what(x);\
  FOR_EACH_3(what,  __VA_ARGS__);
#define FOR_EACH_5(what, x, ...)\
  what(x);\
 FOR_EACH_4(what,  __VA_ARGS__);
#define FOR_EACH_6(what, x, ...)\
  what(x);\
  FOR_EACH_5(what,  __VA_ARGS__);
#define FOR_EACH_7(what, x, ...)\
  what(x);\
  FOR_EACH_6(what,  __VA_ARGS__);
#define FOR_EACH_8(what, x, ...)\
  what(x);\
  FOR_EACH_7(what,  __VA_ARGS__);
#define FOR_EACH_9(what, x, ...)\
  what(x);\
  FOR_EACH_8(what, __VA_ARGS__);
#define FOR_EACH_10(what, x, ...)\
  what(x);\
  FOR_EACH_9(what, __VA_ARGS__);
#define FOR_EACH_11(what, x, ...)\
  what(x);\
  FOR_EACH_10(what, __VA_ARGS__);
#define FOR_EACH_12(what, x, ...)\
  what(x);\
  FOR_EACH_11(what, __VA_ARGS__);
#define FOR_EACH_13(what, x, ...)\
  what(x);\
  FOR_EACH_12(what, __VA_ARGS__);
#define FOR_EACH_14(what, x, ...)\
  what(x);\
  FOR_EACH_13(what, __VA_ARGS__);
#define FOR_EACH_15(what, x, ...)\
  what(x);\
  FOR_EACH_14(what, __VA_ARGS__);
#define FOR_EACH_16(what, x, ...)\
  what(x);\
  FOR_EACH_15(what, __VA_ARGS__);
#define FOR_EACH_17(what, x, ...)\
  what(x);\
  FOR_EACH_16(what, __VA_ARGS__);
#define FOR_EACH_18(what, x, ...)\
  what(x);\
  FOR_EACH_17(what, __VA_ARGS__);
#define FOR_EACH_19(what, x, ...)\
  what(x);\
  FOR_EACH_18(what, __VA_ARGS__);
#define FOR_EACH_20(what, x, ...)\
  what(x);\
  FOR_EACH_19(what, __VA_ARGS__);
#define FOR_EACH_21(what, x, ...)\
  what(x);\
  FOR_EACH_20(what, __VA_ARGS__);
#define FOR_EACH_22(what, x, ...)\
  what(x);\
  FOR_EACH_21(what, __VA_ARGS__);
#define FOR_EACH_23(what, x, ...)\
  what(x);\
  FOR_EACH_22(what, __VA_ARGS__);
#define FOR_EACH_24(what, x, ...)\
  what(x);\
  FOR_EACH_23(what, __VA_ARGS__);
#define FOR_EACH_25(what, x, ...)\
  what(x);\
  FOR_EACH_24(what, __VA_ARGS__);
#define FOR_EACH_26(what, x, ...)\
  what(x);\
  FOR_EACH_25(what, __VA_ARGS__);
#define FOR_EACH_27(what, x, ...)\
  what(x);\
  FOR_EACH_26(what, __VA_ARGS__);
#define FOR_EACH_28(what, x, ...)\
  what(x);\
  FOR_EACH_27(what, __VA_ARGS__);
#define FOR_EACH_29(what, x, ...)\
  what(x);\
  FOR_EACH_28(what, __VA_ARGS__);
#define FOR_EACH_30(what, x, ...)\
  what(x);\
  FOR_EACH_29(what, __VA_ARGS__);
#define FOR_EACH_31(what, x, ...)\
  what(x);\
  FOR_EACH_30(what, __VA_ARGS__);
#define FOR_EACH_32(what, x, ...)\
  what(x);\
  FOR_EACH_31(what, __VA_ARGS__);
#define FOR_EACH_33(what, x, ...)\
  what(x);\
  FOR_EACH_32(what, __VA_ARGS__);
#define FOR_EACH_34(what, x, ...)\
  what(x);\
  FOR_EACH_33(what, __VA_ARGS__);
#define FOR_EACH_35(what, x, ...)\
  what(x);\
  FOR_EACH_34(what, __VA_ARGS__);
#define FOR_EACH_36(what, x, ...)\
  what(x);\
  FOR_EACH_35(what, __VA_ARGS__);
#define FOR_EACH_37(what, x, ...)\
  what(x);\
  FOR_EACH_36(what, __VA_ARGS__);
#define FOR_EACH_38(what, x, ...)\
  what(x);\
  FOR_EACH_37(what, __VA_ARGS__);
#define FOR_EACH_39(what, x, ...)\
  what(x);\
  FOR_EACH_38(what, __VA_ARGS__);
#define FOR_EACH_40(what, x, ...)\
  what(x);\
  FOR_EACH_39(what, __VA_ARGS__);
#define FOR_EACH_41(what, x, ...)\
  what(x);\
  FOR_EACH_40(what, __VA_ARGS__);
#define FOR_EACH_42(what, x, ...)\
  what(x);\
  FOR_EACH_41(what, __VA_ARGS__);
#define FOR_EACH_43(what, x, ...)\
  what(x);\
  FOR_EACH_42(what, __VA_ARGS__);
#define FOR_EACH_44(what, x, ...)\
  what(x);\
  FOR_EACH_43(what, __VA_ARGS__);
#define FOR_EACH_45(what, x, ...)\
  what(x);\
  FOR_EACH_44(what, __VA_ARGS__);
#define FOR_EACH_46(what, x, ...)\
  what(x);\
  FOR_EACH_45(what, __VA_ARGS__);
#define FOR_EACH_47(what, x, ...)\
  what(x);\
  FOR_EACH_46(what, __VA_ARGS__);
#define FOR_EACH_48(what, x, ...)\
  what(x);\
  FOR_EACH_47(what, __VA_ARGS__);
#define FOR_EACH_49(what, x, ...)\
  what(x);\
  FOR_EACH_48(what, __VA_ARGS__);
#define FOR_EACH_50(what, x, ...)\
  what(x);\
  FOR_EACH_49(what, __VA_ARGS__);
#define FOR_EACH_51(what, x, ...)\
  what(x);\
  FOR_EACH_50(what, __VA_ARGS__);
#define FOR_EACH_52(what, x, ...)\
  what(x);\
  FOR_EACH_51(what, __VA_ARGS__);
#define FOR_EACH_53(what, x, ...)\
  what(x);\
  FOR_EACH_52(what, __VA_ARGS__);
#define FOR_EACH_54(what, x, ...)\
  what(x);\
  FOR_EACH_53(what, __VA_ARGS__);
#define FOR_EACH_55(what, x, ...)\
  what(x);\
  FOR_EACH_54(what, __VA_ARGS__);
#define FOR_EACH_56(what, x, ...)\
  what(x);\
  FOR_EACH_55(what, __VA_ARGS__);
#define FOR_EACH_57(what, x, ...)\
  what(x);\
  FOR_EACH_56(what, __VA_ARGS__);
#define FOR_EACH_58(what, x, ...)\
  what(x);\
  FOR_EACH_57(what, __VA_ARGS__);
#define FOR_EACH_59(what, x, ...)\
  what(x);\
  FOR_EACH_58(what, __VA_ARGS__);
#define FOR_EACH_60(what, x, ...)\
  what(x);\
  FOR_EACH_59(what, __VA_ARGS__);
#define FOR_EACH_61(what, x, ...)\
  what(x);\
  FOR_EACH_60(what, __VA_ARGS__);
#define FOR_EACH_62(what, x, ...)\
  what(x);\
  FOR_EACH_61(what, __VA_ARGS__);
#define FOR_EACH_63(what, x, ...)\
  what(x);\
  FOR_EACH_62(what, __VA_ARGS__);
#define FOR_EACH_64(what, x, ...)\
  what(x);\
  FOR_EACH_63(what, __VA_ARGS__);

#define FOR_EACH_(N, what, x, ...) CONCATENATE(FOR_EACH_, N)(what, x, __VA_ARGS__)
#define FOR_EACH(what, x, ...) FOR_EACH_(COUNT_ARGUMENTS(x, __VA_ARGS__), what, x, __VA_ARGS__)

/*****************************************************
 STORE_ARGUMENTS Stores the arguments into an appropriately sized memory block
 Description: For each argument, calculates the sizeof returns the sum
 Author: Benjamin Nye
 NOTE: This may not work reliably if the function receives zero args, depending on compiler
*******************************************************/
#define STORE_ARGUMENT(memBlock, x, offset) memcpy(memBlock+offset, &x, sizeof(x)); offset += sizeof(x)
#define STORE_ARGUMENTS_0(memBlock, offset, ...) 
#define STORE_ARGUMENTS_1(memBlock, offset, x, ...) STORE_ARGUMENT(memBlock, x, offset)
#define STORE_ARGUMENTS_2(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_1(memBlock, offset, __VA_ARGS__)
#define STORE_ARGUMENTS_3(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_2(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_4(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_3(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_5(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_4(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_6(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_5(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_7(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_6(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_8(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_7(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_9(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_8(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_10(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_9(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_11(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_10(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_12(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_11(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_13(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_12(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_14(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_13(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_15(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_14(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_16(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_15(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_17(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_16(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_18(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_17(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_19(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_18(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_20(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_19(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_21(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_20(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_22(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_21(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_23(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_22(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_24(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_23(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_25(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_24(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_26(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_25(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_27(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_26(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_28(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_27(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_29(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_28(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_30(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_29(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_31(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_30(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_32(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_31(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_33(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_32(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_34(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_33(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_35(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_34(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_36(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_35(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_37(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_36(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_38(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_37(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_39(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_38(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_40(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_39(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_41(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_40(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_42(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_41(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_43(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_42(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_44(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_43(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_45(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_44(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_46(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_45(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_47(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_46(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_48(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_47(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_49(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_48(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_50(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_49(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_51(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_50(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_52(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_51(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_53(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_52(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_54(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_53(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_55(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_54(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_56(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_55(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_57(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_56(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_58(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_57(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_59(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_58(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_60(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_59(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_61(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_60(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_62(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_61(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_63(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_62(memBlock, offset, __VA_ARGS__);
#define STORE_ARGUMENTS_64(memBlock, offset, x, ...)\
  STORE_ARGUMENT(memBlock, x, offset);\
  STORE_ARGUMENTS_63(memBlock, offset, __VA_ARGS__);


#define STORE_ARGUMENTS_(N, memBlock, offset, ...) CONCATENATE(STORE_ARGUMENTS_, N)(memBlock, offset, __VA_ARGS__)
#define STORE_ARGUMENTS(memBlock, offset, ...) STORE_ARGUMENTS_(COUNT_ARGUMENTS(__VA_ARGS__), memBlock, offset, __VA_ARGS__)

#define STORE_N_ARGUMENTS(memBlock, offset, n, ...) STORE_ARGUMENTS_(n, memBlock, offset, __VA_ARGS__)
  
/******************************************************
   FOR_EACH_SET_2 Macro
   Adapted from: Gregory Pakosz (alters the original to act on two arguments
   Source: http://stackoverflow.com/questions/1872220/is-it-possible-to-iterate-over-arguments-in-variadic-macros
   Functional up to 128 arguments (in theory).  But should generally be used for filtering or condensing args back to 64 if so.
*******************************************************/
// These catch the cases where no arguments were given (for some reason no args shows up as one arg sometimes)
#define FOR_EACH_SET_2_0(what, sep, ...)
// Pairwise Functions
#define FOR_EACH_SET_2_2(what, sep, _1,_2, ...) what(_1,_2)
#define FOR_EACH_SET_2_4(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_2(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_6(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_4(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_8(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_6(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_10(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_8(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_12(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_10(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_14(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_12(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_16(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_14(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_18(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_16(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_20(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_18(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_22(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_20(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_24(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_22(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_26(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_24(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_28(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_26(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_30(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_28(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_32(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_30(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_34(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_32(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_36(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_34(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_38(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_36(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_40(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_38(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_42(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_40(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_44(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_42(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_46(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_44(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_48(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_46(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_50(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_48(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_52(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_50(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_54(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_52(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_56(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_54(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_58(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_56(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_60(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_58(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_62(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_60(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_64(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_62(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_66(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_64(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_68(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_66(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_70(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_68(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_72(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_70(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_74(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_72(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_76(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_74(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_78(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_76(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_80(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_78(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_82(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_80(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_84(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_82(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_86(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_84(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_88(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_86(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_90(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_88(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_92(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_90(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_94(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_92(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_96(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_94(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_98(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_96(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_100(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_98(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_102(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_100(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_104(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_102(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_106(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_104(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_108(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_106(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_110(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_108(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_112(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_110(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_114(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_112(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_116(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_114(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_118(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_116(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_120(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_118(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_122(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_120(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_124(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_122(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_126(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_124(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2_128(what, sep, _1,_2, ...)\
  what(_1,_2)sep()\
  FOR_EACH_SET_2_126(what, sep, __VA_ARGS__)
  
#define FOR_EACH_SET_2_(N, what, sep, ...) CONCATENATE(FOR_EACH_SET_2_, N)(what, sep, __VA_ARGS__)
#define FOR_EACH_SET_2(what, sep, ...) FOR_EACH_SET_2_(COUNT_ARGUMENTS(__VA_ARGS__), what, sep, __VA_ARGS__)

/******************************************************
   Pairwise Filters and Argument Merging
   By: Benjamin Nye
   Functional up to 64 arguments.
*******************************************************/
#define MERGE_ARGUMENTS_IN_PAIR(a, b) MERGE_ARGUMENTS_IN_PAIR1(a, b) 
#define MERGE_ARGUMENTS_IN_PAIR1(a, b) MERGE_ARGUMENTS_IN_PAIR2(a,b)
#define MERGE_ARGUMENTS_IN_PAIR2(a, b) a b

#define FILTER_FIRST_ARG_IN_PAIR(a, b) FILTER_FIRST_ARG_IN_PAIR1(a,b)
#define FILTER_FIRST_ARG_IN_PAIR1(a, b) FILTER_FIRST_ARG_IN_PAIR2(a,b)
#define FILTER_FIRST_ARG_IN_PAIR2(a, b) b

#define FILTER_SECOND_ARG_IN_PAIR(a, b) FILTER_SECOND_ARG_IN_PAIR1(a, b)
#define FILTER_SECOND_ARG_IN_PAIR1(a, b) FILTER_SECOND_ARG_IN_PAIR2(a, b) 
#define FILTER_SECOND_ARG_IN_PAIR2(a, b) a

#define MERGE_ARGUMENTS_PAIRWISE(...) FOR_EACH_SET_2_(COUNT_ARGUMENTS(__VA_ARGS__), MERGE_ARGUMENTS_IN_PAIR, MAKE_COMMA, __VA_ARGS__)

#define FILTER_ODD_ARGUMENTS(...) FOR_EACH_SET_2_(COUNT_ARGUMENTS(__VA_ARGS__), FILTER_FIRST_ARG_IN_PAIR, MAKE_COMMA, __VA_ARGS__)

#define FILTER_EVEN_ARGUMENTS(...) FOR_EACH_SET_2_(COUNT_ARGUMENTS(__VA_ARGS__), FILTER_SECOND_ARG_IN_PAIR, MAKE_COMMA, __VA_ARGS__)


#endif
