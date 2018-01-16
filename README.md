Build:
	Download and set all third party libs. See include_3rd_party README.
	See CmakeLists.txt on the root folder and build.sh to automatically build.
	Include Openssl f
Windows:
	Openssl: https://slproweb.com/products/Win32OpenSSL.html
	cmake .. -G "Visual Studio 14 2015" -DOPENSSL_ROOT_DIR=C:/OpenSSL-Win322 -DOPENSSL_INCLUDE_DIR=C:/OpenSSL-Win32/include -DBUILD_SHARED_LIBS=OFF

Linux:
	sudo apt-get install libssl-dev
	
