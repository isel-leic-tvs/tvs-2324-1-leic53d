FROM ubuntu

RUN apt -qq -y update && \
    apt -qq -y upgrade && \
    apt -y autoclean && \
    apt -y autoremove

RUN apt -qq -y install net-tools iputils-ping dnsutils curl wget

