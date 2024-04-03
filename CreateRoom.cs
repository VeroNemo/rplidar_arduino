using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

public class CreateRoom : MonoBehaviour
{
public GameObject planePrefab; // Prefab of the plane you want to create
public Material floorMaterial; // Material for the floor
public Material wallMaterial; // Material for the walls

    void Start()
    {
            // Path to your text file
        string filePath = "Assets/lidarData.txt";

        // Read the text file
        string[] lines = File.ReadAllLines(filePath);

        // Loop through each line in the file
        for (int i = 0; i < lines.Length; i++)
        {
            // Split the line by semicolon
            string[] values = lines[i].Split(';');

            // Parse values
            float x = float.Parse(values[0]);
            float y = float.Parse(values[1]);
            float z = float.Parse(values[2]);
            float width = float.Parse(values[3]);
            float height = float.Parse(values[4]);
            float rotationX = float.Parse(values[5]);
            float rotationZ = float.Parse(values[6]);

            // Determine material based on line index
            Material planeMaterial = (i == 0) ? floorMaterial : wallMaterial;

            // Create plane at the specified position and rotation
            CreatePlane(new Vector3(x, y, z), new Vector3(rotationX, 0f, rotationZ), width, height, planeMaterial);
        }
    }

    void CreatePlane(Vector3 position, Vector3 rotation, float width, float height, Material material)
    {
        // Instantiate the plane prefab
        GameObject newPlane = Instantiate(planePrefab, position, Quaternion.Euler(rotation));

        // Set material of the plane
        Renderer renderer = newPlane.GetComponent<Renderer>();
        renderer.material = material;

        // Set scale of the plane
        newPlane.transform.localScale = new Vector3(width, 1f, height);
    }
}
