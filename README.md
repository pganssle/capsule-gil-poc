### GIL Release PoC
Instructions:

1. Clone repository
2. `make`
3. See the behavior *without* PyCapsule_Import: `./gil`

> Waiting for GIL (0)
>
> Gil acquired! (0)
>
> Waiting for GIL (1)
>
> Gil released! (0)
>
> Gil acquired! (1)
>
> Gil released! (1)

4. See the behavior *with* PyCapsule_Import: `/.gil import`

>  Waiting for GIL (0)
>
>  Gil acquired! (0)
>
>  Waiting for GIL (1)
>
>  **Gil acquired! (1)**
>
>  **Gil released! (0)**
>
>  Gil released! (1)
