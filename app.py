from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/')
def home():
    return 'Flask is working!'

@app.route('/generate_route', methods=['POST'])
def generate_route():
    # Return a simple welcome message
    return jsonify({"message": "Welcome to the Robot Tour Guide!"})

if __name__ == '__main__':
    app.run(debug=True)
