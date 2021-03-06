# linked to from dir one level below
include ../v8.mk

# force clang++ since g++ thinks certain things like FunctionCallbackInfo are ambiguous whereas clang++ resolves them just fine
build: 
	g++ -I$(V8)/include main.cc -o main                         \
	-Wl,--start-group                                              \
		$(V8)/out/$(V8_ARCH)/obj.target/third_party/icu/libicuuc.a 	 \
		$(V8)/out/$(V8_ARCH)/obj.target/third_party/icu/libicui18n.a \
		$(V8)/out/$(V8_ARCH)/obj.target/third_party/icu/libicudata.a \
		$(V8)/out/$(V8_ARCH)/obj.target/tools/gyp/libv8_base.x64.a   \
		$(V8)/out/$(V8_ARCH)/obj.target/tools/gyp/libv8_snapshot.a   \
	-Wl,--end-group                                                \
	-lrt

run: build
	./main

clean:
	rm -f ./main

.PHONY: clean build run
