Dependencies
------------

 - boost/math/distributions
 - boost/histogram
 - fmt
 - nlohmann/json

The following mostly used for testing/debug builds. At the moment you need them to build however.

 - catch2
  - cmake target Catch2::Catch2WithMain

Docker development environment
------------------------------

If you want to build the project locally, you can either install the dependencies above and do a cmake build regularily, or you can use a docker dev container.

Navigate to the docker directory and run the following:

    .../webrend $ cd docker
    .../webrend/docker$ sudo ./start_docker_dev_environment.sh

The first time this command is run, docker will build an image, create a container and attach your terminal to it. This may take a while.
After the image has been built, this command will just set up the container and attach your terminal to it.
