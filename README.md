# ValkyrieEngineCommon

Common utilities for Valkyrie Engine

## ConstexprWrapper

The ConstexprWrapper class is used to make and access `constexpr`-specific overloads of functions.

```cpp
// Fast implementation that only works at runtime
float MySquareRoot(float f) { ... }

// Slow implementation that works at compile-time
constexpr ConstexprWrapper<float> MySquareRoot(ConstexprWrapper<float> f) { ... }

float Foo() { ... }

// ConstexprWrapper works with void arguments, too
constexpr ConstexprWrapper<float> Foo(ConstexprWrapper<void>) { ... }

int main()
{
	// Use ForceCXPR(...) to construct a ConstexprWrapper
	constexpr float rootTwo = MySquareRoot(ForceCXPR(2.0f));

	// Calls the non-constexpr overload
	float rootThree = MySquareRoot(3.0f);

	// Constexpr overloads can be chained together
	constexpr float rootFoo = MySquareRoot(Foo(ForceCXPR()));
}
```
## Content

The content class is used to load files from the disk and store them in a central location where they can then be accessed using an assigned string value.

### Loading/Unloading Content

Before one can load content into a container class, the template functions `vlk::ConstructContent` and `vlk::DestroyContent` must be manually specialized.

```cpp
// Content container class
struct MyContent
{
	std::string data;
};
```

ConstructContent is responsible for loading the file at the given path and assembling it into a container class (MyContent in this example).

```cpp
template <>
MyContent* vlk::ConstructContent(const std::string& path)
{
	std::ifstream file(path);

	// path parameter may not point to a valid file
	if (!file.good()) return nullptr;

	// Construct instance of MyContent
	MyContent* content = new MyContent();

	// Read first line of file into content object
	std::getline(file, content->data);

	return content;
}
```
DestroyContent is responsible for doing any necessary cleanup when content is unloaded. Here, we only need to call delete on the object.

```cpp
template <>
void vlk::DestroyContent(MyContent* c)
{
	delete c;
}
```

With that out of the way, we can now actually load our content. The content class will treat all paths as relative to a content prefix. By default, this prefix is 'content/' but this can be changed on a per-template basis:

```cpp
// The content prefix must always end in a trailing slash '/'
Content<MyContent>::SetContentPrefix("content/mycontent/");
```

The content can now be loaded from the disk and assigned an alias:

```cpp
// The full path of the content will expand to 'content/mycontent/relative/path/to/content.file'
Content<MyContent>::LoadContent("relative/path/to/content.file", "SampleContent");
```

Content can now be loaded from anywhere in the program with the alias provided when we loaded it.

```cpp
Content<MyContent>::GetContent("SampleContent");
```

When we're done with a piece of content, you can unload it like so:
```cpp
Content<MyContent>::UnloadContent("SampleContent");
```

### Content Metadata

Optional metadata can be provided for content files in the form of a dedicated meta file. These meta files consist of key-value pairs and are loaded automatically by the content class whenever a content file is loaded.

In order for the content manager to identify metadata for a file, the meta file must be in the same directory as it's content file and must have the same name as the content file, with '.meta' appended to the end (e.g. for a content file 'image.png', the corresponding meta file will be called 'image.png.meta').

A sample meta file is presented below. Meta files have one key-value pair per line which is split along the first '=' character in the line. Lines beginning with '#' characters are treated as comments and are ignored. In the interest of forwards compatibility, the first line of a meta file should begin with a '!' character and identify the version of the meta format. Since no other meta formats have been defined at the time of writing, this should always read '!version=1'.

```
!version=1
meta_value_1=foo
meta value 2=bar

# This is a comment
another meta value=baz
```
