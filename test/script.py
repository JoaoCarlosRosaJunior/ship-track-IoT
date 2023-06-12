import requests
from geopy.distance import geodesic
import json
import time

headers = {
    'Content-Type': 'application/json'
}

url = "https://ship-track.fly.dev/locations/test"

def interpolate_coordinates(point1, point2, num_points):
    lat1, lon1 = point1
    lat2, lon2 = point2
    
    total_distance = geodesic(point1, point2).meters
    
    increment = total_distance / (num_points + 1)
    
    coordinates = []
    for i in range(1, num_points + 1):
        distance = i * increment
        fraction = distance / total_distance
        
        lat = int(round((lat1 + fraction * (lat2 - lat1)) * 1000000))
        lon = int(round((lon1 + fraction * (lon2 - lon1)) * 1000000))
        
        coordinates.append((lat, lon))
    
    return coordinates

def send_coordinates_to_api(coordinates):
    
    for lat, lon in coordinates:
        payload = json.dumps({
            "deviceId": orderId,
            "latitude": lat,
            "longitude": lon
            })
        
        response = requests.request("POST", url, headers=headers, data=payload)
        
        if response.status_code == 201:
            print("Coordinates sent successfully.")
        else:
            print("Error sending coordinates. Status code:", response)
        
        time.sleep(1)

# Example usage
print("Example of point input(latitude,longitude): 40.7128,-74.0060")
point1 = tuple(float(x) for x in input("Enter latitude and longitude of point 1 (comma-separated): ").split(","))
point2 = tuple(float(x) for x in input("Enter latitude and longitude of point 2 (comma-separated): ").split(","))
num_points = int(input("Enter the number of interpolated points: "))
orderId = input("Enter the orderId: ")

interpolated_points = interpolate_coordinates(point1, point2, num_points)

# Send the interpolated coordinates to the API
send_coordinates_to_api(interpolated_points)
