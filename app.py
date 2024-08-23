from flask import Flask, send_from_directory, request, jsonify
import subprocess
import tempfile
import os

app = Flask(__name__, static_folder='build', static_url_path='')

@app.route('/')
def index():
    return send_from_directory(app.static_folder, 'index.html')

@app.route('/generate_route', methods=['POST'])
def generate_route():
    try:
        data = request.json.get('locations', [])

        # Create a temporary file to store the POI data
        with tempfile.NamedTemporaryFile(delete=False, mode='w', newline='') as temp_file:
            for location in data:
                poi = location.get('name')
                description = location.get('description')
                if poi and description:
                    temp_file.write(f"{poi}|{description}\n")
            temp_file_path = temp_file.name

        # Call the C++ program with the temporary file as input
        result = subprocess.run(['./Tour Guide Generator/robot', temp_file_path], capture_output=True, text=True)
        output = result.stdout
        os.remove(temp_file_path)
        return jsonify({"route": output})

    except Exception as e:
        print(f"Error: {e}")
        return jsonify({"error": "An error occurred while generating the route."}), 500

if __name__ == '__main__':
    app.run()
