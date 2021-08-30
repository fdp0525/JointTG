FROM adnrv/opencv:3.4

RUN apt-get install -y libflann-dev libboost-system-dev libboost-filesystem-dev libomp-dev

COPY bin/JointTG /usr/bin/JointTG

COPY lib /usr/lib
