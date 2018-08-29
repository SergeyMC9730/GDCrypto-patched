#ifndef _gdcrypto_hpp
#define _gdcrypto_hpp

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "base64.hpp"
#include "sha1.hpp"
#include "zlib/zlib.h"

/*
   General XOR keys, used for various reasons
*/

const auto GJP_KEY = "37526";
const auto MESSAGE_KEY = "14251";
const auto LEVEL_KEY = "41274";
const auto COMMENT_KEY = "29481";
const auto CHALLENGES_KEY = "19847";
const auto REWARDS_KEY = "59182";
const auto LIKERATE_KEY = "58281";

/*
   Const value used by DecodeSavegame()
*/

const auto CHUNK = 16384;

/*
   Structures of the CHKs
   CHKs are encoded strings that contains data used by the server to validate requests.
   Every CHK is encoded in this way:
   Raw data -> SHA1 string -> xor (every CHK has a different key) -> base64
   The raw data is a combination of various values and a salt, which also differ between CHKs.
   Below is shown how every CHK raw datas is structured.
*/
typedef enum
{
	//Args: Special, ItemID, Like, Type, RS, AccountID, UDID, UUID
	LIKE_CHK = 0,
	//Args: LevelID, Stars, RS, AccountID, UDID, UUID
	RATE_LEVEL_CHK = 1,
	//Args: Username, Comment, LevelID, Percentage, Comment Type (0 = Level, 1 = User)
	UPLOAD_COMMENT_CHK = 2,
	//Args: LevelID, Inc, RS, AccountID, UDID, UUID
	DOWNLOAD_LEVEL_CHK = 3
} ServerChecks;

//Add description for each function

/**/
std::string RobtopCipher_Encode(
	const char * Buffer,
	size_t Size,
	const std::string& Key);

/**/
std::string RobtopCipher_Decode(
	const std::string& Buffer, 
	const std::string& Key);

/**/
std::string GenerateCHK(
	ServerChecks Type,
	const std::vector<std::string>& Args);

/**/
std::string DecodeSavegame(
	char * Src,
	size_t SizeIn);

#endif