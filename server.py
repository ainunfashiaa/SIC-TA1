from flask import Flask, request, jsonify

app = Flask(__name__)

base = []

@app.route('/post-data', methods=['POST'])
def receive_data():
    global base
    data = request.get_json()
    lux = data['lux']
    SubData = [lux]

    base = SubData

    print("Data diterima intensitas cahaya:", lux, "lux ")
    
    response = {'message': 'Data diterima'}
    return jsonify(response), 200

@app.route('/post-data', methods=['GET'])
def dapat_data():
    global base
    return jsonify({'lux': base[0],}) if base else jsonify({'message': 'No data available'})

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)
