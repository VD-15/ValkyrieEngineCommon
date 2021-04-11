#include "TestValues.hpp" 
#include "ValkyrieEngineCommon/Content.hpp"
#include <fstream>
#include <stdexcept>
#include <string>

using namespace vlk;

int constructCalls = 0;
int destructCalls = 0;

int loadedEvents = 0;
int unloadedEvents = 0;

struct MyContent
{
	std::string data;
};

class MyEventListener :
	public EventListener<Content<MyContent>::LoadEvent>,
	public EventListener<Content<MyContent>::UnloadEvent>
{
	public:
	typedef Content<MyContent>::LoadEvent LoadEvent;
	typedef Content<MyContent>::UnloadEvent UnloadEvent;

	void OnEvent(const LoadEvent&) override
	{
		loadedEvents++;
	}

	void OnEvent(const UnloadEvent&) override
	{
		unloadedEvents++;
	}
};

template<>
MyContent* vlk::ConstructContent(const std::string& path)
{
	std::ifstream file(path);
	if (!file.good()) return nullptr;
	constructCalls++;
	MyContent* c = new MyContent();
	std::getline(file, c->data);
	return c;
}

template<>
void vlk::DestroyContent(MyContent* c)
{
	destructCalls++;
	delete c;
}

TEST_CASE("Content management")
{
	MyEventListener ev;

	//SECTION("Load content")
	{
		REQUIRE(Content<MyContent>::LoadContent("TestCase1", "test_1"));
		REQUIRE(!Content<MyContent>::LoadContent("TestCase2", "test_2"));

		REQUIRE(constructCalls == 1);
		REQUIRE(destructCalls == 0);

		REQUIRE(loadedEvents == 1);
		REQUIRE(unloadedEvents == 0);
	}

	const MyContent* c1;
	const MyContent* c2;

	//SECTION("Get content")
	{
		c1 = Content<MyContent>::GetContent("test_1");
		c2 = Content<MyContent>::GetContent("test_2");

		REQUIRE(constructCalls == 1);
		REQUIRE(destructCalls == 0);

		REQUIRE(loadedEvents == 1);
		REQUIRE(unloadedEvents == 0);

		REQUIRE(c1 != nullptr);
		REQUIRE(c2 == nullptr);
	}

	//SECTION("Get metadata")
	{
		REQUIRE(c1->data == "Test case 1 sample data.");
		REQUIRE(Content<MyContent>::GetMetadata("test_1", "meta_1") == "pass");
		REQUIRE(Content<MyContent>::GetMetadata("test_1", "meta_2") == "second metadata value");
		REQUIRE(Content<MyContent>::GetMetadata("test_1", "meta_3") == "");
		REQUIRE(Content<MyContent>::GetMetadata("test_1", "meta_4") == "");
		REQUIRE(Content<MyContent>::GetMetadata("test_2", "meta_1") == "");
		REQUIRE(Content<MyContent>::GetMetadata("test_2", "meta_2") == "");
		REQUIRE(Content<MyContent>::GetMetadata("test_2", "meta_3") == "");
		REQUIRE(Content<MyContent>::GetMetadata("test_2", "meta_4") == "");
	}

	//SECTION("Load replace content")
	{
		REQUIRE(Content<MyContent>::LoadContent("TestCaseR", "test_1"));

		c1 = Content<MyContent>::GetContent("test_1");

		REQUIRE(c1 != nullptr);

		REQUIRE(constructCalls == 2);
		REQUIRE(destructCalls == 1);

		REQUIRE(loadedEvents == 2);
		REQUIRE(unloadedEvents == 1);

		REQUIRE(Content<MyContent>::GetMetadata("test_1", "meta_1") == "pass");
		REQUIRE(Content<MyContent>::GetMetadata("test_1", "meta_2") == "repeat metadata value");
		REQUIRE(Content<MyContent>::GetMetadata("test_1", "meta_3") == "");
		REQUIRE(Content<MyContent>::GetMetadata("test_1", "meta_4") == "");
	}

	//SECTION("Content prefix")
	{
		REQUIRE(Content<MyContent>::GetContentPrefix() == "content/");
		
		REQUIRE_THROWS_AS(
			Content<MyContent>::SetContentPrefix("invalid prefix"), 
			std::invalid_argument);

		REQUIRE(Content<MyContent>::GetContentPrefix() == "content/");

		Content<MyContent>::SetContentPrefix("other_content/");

		REQUIRE(Content<MyContent>::GetContentPrefix() == "other_content/");
	}

	//SECTION("Load content from other directory")
	{
		REQUIRE(Content<MyContent>::LoadContent("TestCase2", "test_2"));

		c2 = Content<MyContent>::GetContent("test_2");

		REQUIRE(c2 != nullptr);

		REQUIRE(constructCalls == 3);
		REQUIRE(destructCalls == 1);

		REQUIRE(loadedEvents == 3);
		REQUIRE(unloadedEvents == 1);

		REQUIRE(c2->data == "Test case 2 sample data.");

		REQUIRE(Content<MyContent>::GetMetadata("test_2", "meta_1") == "pass");
		REQUIRE(Content<MyContent>::GetMetadata("test_2", "meta_2") == "third metadata value");
		REQUIRE(Content<MyContent>::GetMetadata("test_2", "") == "");
		REQUIRE(Content<MyContent>::GetMetadata("test_2", "no value") == "");
		REQUIRE(Content<MyContent>::GetMetadata("test_2", "meta_3") == "");
		REQUIRE(Content<MyContent>::GetMetadata("test_2", "meta_4") == "");
	}

	//SECTION("Unload content")
	{
		REQUIRE(Content<MyContent>::UnloadContent("test_1"));
		REQUIRE(!Content<MyContent>::UnloadContent("test_1"));
		REQUIRE(Content<MyContent>::UnloadContent("test_2"));
		REQUIRE(!Content<MyContent>::UnloadContent("test_2"));

		REQUIRE(constructCalls == 3);
		REQUIRE(destructCalls == 3);

		REQUIRE(loadedEvents == 3);
		REQUIRE(unloadedEvents == 3);
		
		c1 = Content<MyContent>::GetContent("test_1");
		c2 = Content<MyContent>::GetContent("test_2");

		REQUIRE(c1 == nullptr);
		REQUIRE(c2 == nullptr);

		REQUIRE(Content<MyContent>::GetMetadata("test_1", "meta_1") == "");
		REQUIRE(Content<MyContent>::GetMetadata("test_1", "meta_2") == "");
		REQUIRE(Content<MyContent>::GetMetadata("test_1", "meta_3") == "");
		REQUIRE(Content<MyContent>::GetMetadata("test_1", "meta_4") == "");
		REQUIRE(Content<MyContent>::GetMetadata("test_2", "meta_1") == "");
		REQUIRE(Content<MyContent>::GetMetadata("test_2", "meta_2") == "");
		REQUIRE(Content<MyContent>::GetMetadata("test_2", "meta_3") == "");
		REQUIRE(Content<MyContent>::GetMetadata("test_2", "meta_4") == "");
	}
}
