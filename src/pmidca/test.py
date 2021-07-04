"""
python program to test the functionality of the pmidca in moos
This file contains functions to test the three functionalities of the pmidca app
                        1. Communicates vehicle location (x,y), speed and heading
                        2. Communicates Detected mines
                        3. Subscribes way_points from midca
"""

import zmq, time

# establish subscriber connection for remus
context = zmq.Context()
subscriber_remus = context.socket(zmq.SUB)
subscriber_remus.setsockopt(zmq.SUBSCRIBE, "Hazard")
subscriber_remus.setsockopt(zmq.RCVTIMEO, -1)
subscriber_remus.connect("tcp://127.0.0.1:4999")



# connection for publishing the waypoints
publisher = context.socket(zmq.PUB)
publisher.connect("tcp://127.0.0.1:5999")

# Function to test Communication functionality of the vehicle
def communicate(n):
    """
    params n: number of times it should recieve message
    Should recieve the vehicle locations when this function is run
    """


    if n == 0:
        return None

    subscriber_remus.setsockopt(zmq.SUBSCRIBE, "Vehicle")
    # get the message from the ip address
    [address, content] = subscriber_remus.recv_multipart(copy=False)
    subscriber_remus.setsockopt(zmq.UNSUBSCRIBE, "Vehicle")


    if str(address) == "Vehicle":
        # print the current position
        #print (content)
        pass

    subscriber_remus.setsockopt(zmq.SUBSCRIBE, "SearchComplete")
    # get the message from the ip address
    [address, content] = subscriber_remus.recv_multipart(copy=False)
    subscriber_remus.setsockopt(zmq.UNSUBSCRIBE, "SearchComplete")

    if str(address) == "SearchComplete":
        # print the current position
        print (content)

    communicate(n-1)


def send_waypoints():
    """
    Should send the way_points when this function is run
    """
    time.sleep(0.25)

    message = [b"Vehicle", b"point = 1,-62 # speed= 1.0"]

    publisher.send_multipart(message)

    print ("Sent Message : ", message)


def RemoveMine():
    """
    Should remove mine
    """
    time.sleep(0.3)

    message = [b"RemoveHazard", "5"]

    publisher.send_multipart(message)

    print ("Sent Message : ", message)


def AddMine():
    """
    Should add mine
    """

    time.sleep(0.3)

    message = [b"AddHazard", b"x=10,y=10,label= 10, type=hazard"]

    publisher.send_multipart(message)

    print ("Sent Message : ", message)


if __name__ == "__main__":
    send_waypoints()
    #time.sleep(13)
    #communicate(10)
    #RemoveMine()
    #AddMine()
