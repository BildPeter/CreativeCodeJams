import OSC
import markovify

# ----------------
print 'Reading text'
with open('old/texts_all.txt') as file:
    text = file.read()
markovGenerator = markovify.Text( text )

# --- JSON (actually slower)
# with open('punkMarkov.json') as file:
#     text = file.read()
# markovGenerator = markovify.Text.from_json( text )

# ----------------
print 'Init OSC'
oscSender_HostPort = ( '127.0.0.1', 6000 )  # to OpenFrameworks
oscReciever_HostPort = ( '127.0.0.1', 5000 )  # python
oscSender               = OSC.OSCClient( )
oscReceiver = OSC.ThreadingOSCServer( oscReciever_HostPort )
oscSender.connect( oscSender_HostPort )

adressCreate    = "/create"
adressText      = "/text"

print 'Init done'

def recieveMessage( addr, tags, stuff, source ):
    inputLength = int( stuff[ 0 ] )
    print "Received message:", inputLength
    text = str( markovGenerator.make_short_sentence( inputLength ) )
    print "sending message: " + text

    messageToSend = OSC.OSCMessage()
    messageToSend.setAddress( adressText )
    messageToSend.append( text )
    oscSender.send( messageToSend )
    return


print 'Listening'

oscReceiver.addMsgHandler( adressCreate, recieveMessage )
oscReceiver.serve_forever( )  # nothing after that works

