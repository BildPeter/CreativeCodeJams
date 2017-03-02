from flask import Flask, render_template, redirect, request
import markovify

with open('old/texts_all.txt') as file:
    text = file.read()
markovGenerator = markovify.Text( text )


app = Flask(__name__)

@app.route('/')
def simplePage():
    author = 'Peter'
    name = 'Fucker'
    sentenceOutput = "Test"
    return render_template('index.html', author=author, name=name, sentenceOutput=sentenceOutput )

@app.route( '/sentence', methods=['POST', 'GET'] )
def sentenceGen():
    author = 'Peter'
    name = 'Fucker'
    if request.method == 'POST':
        startWord = str( request.form['Start word'] )
        print( startWord )
        sentenceOutput = markovGenerator.make_sentence_with_start( startWord ).decode( 'UTF-8' )
        print( sentenceOutput)
        return render_template('index.html', author=author, name=name, sentenceOutput=sentenceOutput)
    elif request.method == 'GET':
        return render_template('index.html', author=author, name=name )

if __name__ == '__main__':
    app.run()

