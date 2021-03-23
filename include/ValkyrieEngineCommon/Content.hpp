#ifndef VLK_CONTENT_HPP
#define VLK_CONTENT_HPP

#include "ValkyrieEngine/EventBus.hpp"
#include "ValkyrieEngine/ValkyrieDefs.hpp"
#include <fstream>
#include <mutex>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <shared_mutex>

namespace vlk
{
	/*!
	 * \brief Constructs content of type T.
	 * 
	 * This function is responsible for constructing an instance of T and
	 * returning an owning pointer to T. This function is called by 
	 * vlk::Content<T>::LoadContent(const std::string& const std::string&) and
	 * must be specialized before it can be invoked. If this unspecialized
	 * template is invoked, it will fail a <tt>static_assert</tt> at compile
	 * time and throw a <tt>std::runtime_error</tt> at runtime.
	 *
	 * This function must not invoke any member of <tt>vlk::Content<T></tt>
	 * while it is executing.
	 *
	 * This function is not responsible for loading metadata.
	 *
	 * \returns An owning pointer to an instance of T if constructing the
	 * content from the disk succeeds, otherwise returns nullptr.
	 *
	 * \param path The location of the content file on the disk.
	 */
	template <typename T>
	VLK_NODISCARD T* ConstructContent(const std::string& path)
	{
		VLK_STATIC_ASSERT_MSG((!std::is_same<T, T>::value), "Generic template for vlk::ConstructContent being compiled. Template must be specialized.");
		throw std::runtime_error("Generic template for vlk::ConstructContent called. Template must be specialized.");
		return nullptr;
	}

	/*!
	 * \brief Destroys content of type T.
	 * 
	 * This function is responsible for destroying an instance of T and This
	 * function is called by 
	 * vlk::Content<T>::LoadContent(const std::string&, const std::string&) and
	 * vlk::Content<T>::UnloadContent(const std::string&) and must be
	 * specialized before either can be invoked. If this unspecialized template
	 * is invoked, it will fail a <tt>static_assert</tt> at compile time and
	 * throw a <tt>std::runtime_error</tt> at runtime.
	 *
	 * This function must not invoke any member of <tt>vlk::Content<T></tt>
	 * while it is executing.
	 *
	 * \param t The instance of T to destroy.
	 */
	template <typename T>
	void DestroyContent(T* t)
	{
		VLK_STATIC_ASSERT_MSG((!std::is_same<T, T>::value), "Generic template for vlk::ConstructContent being compiled. Template must be specialized.");
		throw std::runtime_error("Generic template for vlk::ConstructContent called. Template must be specialized.");
	}

	template <typename T>
	class Content
	{
		static void LoadMetadata(const std::string& path, const std::string& alias)
		{
			std::ifstream metaFile(path);

			if (!metaFile.good()) return;

			std::string str;
			while (std::getline(metaFile, str))
			{
				//No data, on line
				if (str.length() == 0) continue;

				//Line is a comment
				if (str[0] == '#') continue;
				if (str[0] == '!') continue;

				Size split = str.find_first_of('=');
				//No key or no value or no '=' character, continue ro next line
				if (split == 0 | split == str.size() | split == std::string::npos) continue;

				metadata.insert(std::make_pair(
					alias,
					std::make_pair(
						str.substr(0, split),
						str.substr(split + 1))));
			}
		}

		static std::string contentPrefix;
		static std::unordered_map<std::string, T*> content;
		static std::unordered_multimap<std::string, std::pair<std::string, std::string>> metadata;
		static VLK_SHARED_MUTEX_TYPE mtx;
		public:

		/*!
		 * \brief An event sent whenever content of type T is loaded.
		 *
		 * \ts
		 * May only be sent from the main thread.<br>
		 * Resource locking must be handled externally.<br>
		 * Shared access to the Content<T> class may be obtained.<br>
		 */
		struct LoadEvent
		{
			const T* const content;
			const std::string alias;
		};

		/*!
		 * \brief An event sent whenever content of type T is unloaded.
		 *
		 * \ts
		 * May only be sent from the main thread.<br>
		 * Resource locking must be handled externally.<br>
		 * Shared access to the Content<T> class may be obtained.<br>
		 */
		struct UnloadEvent
		{
			const T* const content;
			const std::string alias;
		};

		/*!
		 * \brief Changes the content prefix for this class.
		 *
		 * The content prefix is a string that is prepended to the <tt>path</tt>
		 * argument of <tt>vlk::Content<T>::LoadContent(const std::string&,
		 * const std::string&)</tt> when loading content from the disk. By
		 * default, the content prefix is <tt>"content/"<tt>.
		 *
		 * \param prefix The new content prefix for this class, must end with a
		 * trailing slash ('/') character.
		 *
		 * \throws std::invalid_argument if <tt>prefix</tt> does not end with a 
		 * trailing slash ('/').
		 *
		 * \ts
		 * May be called from any thread.<br>
		 * Resource locking is handled internally.<br>
		 * Unique access to this class is required.<br>
		 * This function may block the calling thread.<br>
		 */
		static inline void SetContentPrefix(const std::string& prefix)
		{
			std::unique_lock<VLK_SHARED_MUTEX_TYPE> ulock(mtx);
			if ((*prefix.crbegin()) != '/')
			{
				throw std::invalid_argument("Prefix must end in a forward slash character.");
				return;
			}

			contentPrefix = prefix;
		}

		/*!
		 * \brief Gets the current content prefix of this class.
		 *
		 * The content prefix is a string that is prepended to the <tt>path</tt>
		 * argument of <tt>vlk::Content<T>::LoadContent(const std::string&,
		 * const std::string&)</tt> when loading content from the disk. By
		 * default, the content prefix is <tt>"content/"<tt>.
		 *
		 * \ts
		 * May be called from any thread.<br>
		 * Resource locking is handled internally.<br>
		 * Shared access to this class is required.<br>
		 * This function may block the calling thread.<br>
		 */
		static inline std::string GetContentPrefix()
		{
			std::shared_lock<VLK_SHARED_MUTEX_TYPE> slock(mtx);
			return contentPrefix;
		}

		//TODO: Metadata guide
		/*!
		 * \brief Loads content from the disk.
		 *
		 * This function calls the template functions
		 * <tt>vlk::ConstructContent(const std::string)</tt> and
		 * <tt>vlk::DestroyContent(T*)</tt> internally. These functions must 
		 * be specialized before they can be invoked.
		 *
		 * This function will also load metadata from a corresponding meta file
		 * if one is found. See the guide on metadata files for information on
		 * how to write one.
		 *
		 * This function sends a <tt>LoadEvent</tt> if the
		 * content is loaded successfully.
		 *
		 * \param path The path to the file to load the content from, relative
		 * to the current content prefix.
		 *
		 * \param alias The alias to assign the content once loaded. This
		 * string will be used as the key to retrieve the content with
		 * <tt>vlk::Content<T>::GetContent(const std::string&)</tt>.
		 *
		 * \returns true if the content loads successfully, false otherwise.
		 *
		 * \ts
		 * Must only be called from the main thread.<br>
		 * Resource locking is handled internally.<br>
		 * Unique access to this class is required.<br>
		 * This function may block the calling thread.<br>
		 *
		 * \sa vlk::Content<T>::SetContentPrefix(const std::string&)
		 * \sa vlk::Content<T>::GetContentPrefix()
		 * \sa vlk::Content<T>::UnloadContent(const std::string&)
		 */
		static inline bool LoadContent(const std::string& path, const std::string& alias)
		{
			std::unique_lock<VLK_SHARED_MUTEX_TYPE> ulock(mtx, std::defer_lock);
			std::shared_lock<VLK_SHARED_MUTEX_TYPE> slock(mtx);

			T* t = vlk::ConstructContent<T>(contentPrefix + path);

			//Content construction failed
			if (!t) return false;

			//erase existing entry
			auto it = content.find(alias);
			if (it != content.end())
			{
				SendEvent(UnloadEvent{it->second, alias});

				slock.unlock();
				ulock.lock();

				//erase any existing metadata
				metadata.erase(alias);

				vlk::DestroyContent(it->second);

				//insert new content
				it->second = t;
			}
			else
			{
				slock.unlock();
				ulock.lock();
				//insert new content
				content.insert(std::make_pair(alias, t));
			}

			//Load metadata
			LoadMetadata(contentPrefix + path + ".meta", alias);

			ulock.unlock();

			vlk::SendEvent(LoadEvent{t, alias});

			return true;
		}

		/*!
		 * \brief Unloads and destroys content
		 *
		 * This function calls the template function
		 * <tt>vlk::DestroyContent(T*)</tt> internally. This function must 
		 * be specialized before it can be invoked.
		 *
		 * This function sends an <tt>UnloadEvent</tt> if the
		 * content is unloaded successfully.
		 *
		 * \param alias The alias of the content to be unloaded.
		 *
		 * \returns true if the content unloads successfully, false otherwise.
		 *
		 * \ts
		 * Must only be called from the main thread.<br>
		 * Resource locking is handled internally.<br>
		 * Unique access to this class is required.<br>
		 * This function may block the calling thread.<br>
		 *
		 * \sa vlk::Content<T>::LoadContent(const std::string&, const std::string&)
		 */
		static inline bool UnloadContent(const std::string& alias)
		{
			//Find content 
			std::unique_lock<VLK_SHARED_MUTEX_TYPE> ulock(mtx, std::defer_lock);
			std::shared_lock<VLK_SHARED_MUTEX_TYPE> slock(mtx);
			auto it = content.find(alias);

			//Check if content does not exist
			if (it == content.end()) return false;

			vlk::SendEvent(UnloadEvent{it->second, alias});
			slock.unlock();
			ulock.lock();

			metadata.erase(alias);
			vlk::DestroyContent<T>(it->second);
			content.erase(alias);

			return true;
		}

		/*!
		 * \brief Retrieves loaded content.
		 *
		 * \param alias The alias of the loaded content to get.
		 *
		 * \return A pointer to an instance of T or nullptr if no content with
		 * the provided alias was found.
		 *
		 * \ts
		 * Must only be called from the main thread.<br>
		 * Resource locking is handled internally.<br>
		 * Shared access to this class is required.<br>
		 * This function may block the calling thread.<br>
		 */
		static inline const T* GetContent(const std::string& alias)
		{
			std::shared_lock<VLK_SHARED_MUTEX_TYPE> slock(mtx);
			auto it = content.find(alias);
			if (it == content.end()) return nullptr;
			return it->second;
		}

		/*!
		 * \brief Gets a metadata value associated with a piece of content.
		 *
		 * \param alias The alias of a loaded piece of content to look up.
		 * \param key The name of the metadata field to look up.
		 *
		 * \returns The value of the metadata field for the given content or
		 * an empty string if either the content or the key were not found.
		 */
		static inline std::string GetMetadata(const std::string& alias, const std::string& key)
		{
			std::shared_lock<VLK_SHARED_MUTEX_TYPE> slock(mtx);
			auto search = metadata.equal_range(alias);
			for (auto it = search.first; it != search.second; it++)
			{
				if (it->second.first == key) return it->second.second;
			}

			return "";
		}
	};

	template <typename T>
	std::string Content<T>::contentPrefix = "content/";

	template <typename T>
	std::unordered_map<std::string, T*> Content<T>::content;

	template <typename T>
	std::unordered_multimap<std::string, std::pair<std::string, std::string>> Content<T>::metadata;

	template <typename T>
	VLK_SHARED_MUTEX_TYPE Content<T>::mtx;
}

#endif
