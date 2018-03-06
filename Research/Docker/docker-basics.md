
# Docker Basics

Some simple docker commands

```
docker --version
docker-compose --version
docker-machine --version

docker ps
docker ps -a

docker verion
docker info
```

Run hello world

- Will pull image from Docker Hub and start a container

```
docker run hello-world
```

Run ubuntu container

```
docker run -it ubuntu bash
```

Search

```
docker search ubuntu
```

Download image

```
docker pull ubuntu
```

Start container and pass a command to it

```
docker run ubuntu /bin/echo "hello world"
```

Docker help
```
// to get help ..
docker help run
```

Docker run container and connect to it
```
docker run -i -t ubuntu

apt-get update
apt-get install nodejs
apt-get install nodejs-legacy
apt-get install npm

npm install -g express-generator

exit

docker commit -a "Your Name &lt;youremail@email.com&gt;" -m "node and express" CONTAINER_ID node-express:0.1
docker commit -a "Heiko Risser heiko@codeforte.com" -m "node and express" 8e9ae1f26041 node-express:0.1

```






















