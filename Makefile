ifndef BOARD
	BOARD=mimxrt1060_evkb
endif

DOCKER_IMAGE=pitchaero/zephyrrtos:v3.7.0LTS

ifdef SAMPLE
	SOURCE_DIR= -v `pwd`/$(SAMPLE):/app/application
else
	SOURCE_DIR= -v `pwd`/application:/app/application
endif

USER := $(shell whoami)

DIR_MOUNTS=-v /dev/bus/usb:/dev/bus/usb \
	   -e DISPLAY --net=host \
	   -v /tmp/.X11-unix:/tmp/.X11-unix:ro \
	   -v `pwd`/.vscode:/app/.vscode \
	   -v `pwd`/.aws:/root/.aws \
	   -v `pwd`/build:/app/build \
	   -v `pwd`/samples:/app/samples \
	   $(SOURCE_DIR)

# syntax is -v <where the file is locally>:<where you want it in the docker container>
SDK_CHANGES= \
	   -v `pwd`/sdk_mods/modem_cellular.c:/app/zephyr/drivers/modem/modem_cellular.c

RUN_DOCKER_CMD=xhost +Local:* ; xhost ; docker run -t -i --privileged $(DIR_MOUNTS) $(SDK_CHANGES) $(DOCKER_IMAGE) 

all: flash

build: compile_app

mount: 
	$(RUN_DOCKER_CMD) 

clean:
	@echo we request sudo here because of docker file permission issues
	sudo rm -rf build
	sudo chown -R $(USER):$(USER) *

compile_app: 
	$(RUN_DOCKER_CMD) west build -b $(BOARD) application 
	
flash: build 
	$(RUN_DOCKER_CMD) west flash
