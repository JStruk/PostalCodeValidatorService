/* FILE         : CIniFile
* PROJECT       : SOA_A1
* PROGRAMMER    : Justin Struk
* FIRST VERSION : 2019-11-28
* DESCRIPTION   : Class for managing *.ini configuration files
*	Code from here -> https://www.codeproject.com/Articles/8342/CIniFile-Class-for-C-A-robust-cross-platform-INI-f
*/

/*  NAME    : CIniFile
*   PURPOSE : Managing *.ini configuration files
*/

#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
using namespace std;

class CIniFile
{
public:
	struct Record
	{
		string Comments;
		char Commented;
		string Section;
		string Key;
		string Value;
	};

	enum CommentChar
	{
		Pound = '#',
		SemiColon = ';'
	};

	CIniFile(void);
	virtual ~CIniFile(void);

	static bool AddSection(string SectionName, string FileName);
	static bool CommentRecord(CommentChar cc, string KeyName,string SectionName,string FileName);
	static bool CommentSection(char CommentChar, string SectionName, string FileName);
	static string Content(string FileName);
	static bool Create(string FileName);
	static bool DeleteRecord(string KeyName, string SectionName, string FileName);
	static bool DeleteSection(string SectionName, string FileName);
	static vector<Record> GetRecord(string KeyName, string SectionName, string FileName);
	static vector<Record> GetSection(string SectionName, string FileName);
	static vector<string> GetSectionNames(string FileName);
	static string GetValue(string KeyName, string SectionName, string FileName);
	static bool RecordExists(string KeyName, string SectionName, string FileName);
	static bool RenameSection(string OldSectionName, string NewSectionName, string FileName);
	static bool SectionExists(string SectionName, string FileName);
	static bool SetRecordComments(string Comments, string KeyName, string SectionName, string FileName);
	static bool SetSectionComments(string Comments, string SectionName, string FileName);
	static bool SetValue(string KeyName, string Value, string SectionName, string FileName);
	static bool Sort(string FileName, bool Descending);
	static bool UnCommentRecord(string KeyName,string SectionName,string FileName);
	static bool UnCommentSection(string SectionName, string FileName);

private:
	static vector<Record> GetSections(string FileName);
	static bool Load(string FileName, vector<Record>& content);	
	static bool Save(string FileName, vector<Record>& content);

	struct RecordSectionIs : std::unary_function<Record, bool>
	{
		std::string section_;

		RecordSectionIs(const std::string& section): section_(section){}

		bool operator()( const Record& rec ) const
		{
			return rec.Section == section_;
		}
	};

	struct RecordSectionKeyIs : std::unary_function<Record, bool>
	{
		std::string section_;
		std::string key_;

		RecordSectionKeyIs(const std::string& section, const std::string& key): section_(section),key_(key){}

		bool operator()( const Record& rec ) const
		{
			return ((rec.Section == section_)&&(rec.Key == key_));
		}
	};

	struct AscendingSectionSort
	{
		bool operator()(Record& Start, Record& End)
		{
			return Start.Section < End.Section;
		}
	};

	struct DescendingSectionSort
	{
		bool operator()(Record& Start, Record& End)
		{
			return Start.Section > End.Section;
		}
	};

	struct AscendingRecordSort
	{
		bool operator()(Record& Start, Record& End)
		{
			return Start.Key < End.Key;
		}
	};

	struct DescendingRecordSort
	{
		bool operator()(Record& Start, Record& End)
		{
			return Start.Key > End.Key;
		}
	};
};