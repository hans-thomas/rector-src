<?php declare(strict_types=1);

namespace Rector\Rector\Dynamic\Configuration;

use Webmozart\Assert\Assert;

final class ArgumentReplacerItemRecipe
{
    /**
     * @var string
     */
    private $class;
    /**
     * @var string
     */
    private $method;
    /**
     * @var int
     */
    private $position;
    /**
     * @var string
     */
    private $type;

    /**
     * @var mixed
     */
    private $defaultValue;

    /**
     * @var string[]
     */
    private $replaceMap = [];

    /**
     * @param mixed $defaultValue
     * @param string[] $replaceMap
     */
    private function __construct(string $class, string $method, int $position, string $type, $defaultValue = null, array $replaceMap)
    {
        $this->class = $class;
        $this->method = $method;
        $this->position = $position;
        $this->type = $type;
        $this->defaultValue = $defaultValue;
        $this->replaceMap = $replaceMap;
    }

    public static function createFromArray(array $data): self
    {
        // @todo: make exceptions clear for end user
        Assert::keyExists($data, 'class');
        Assert::keyExists($data, 'method');
        Assert::keyExists($data, 'position');
        Assert::keyExists($data, 'type');

        if ($data['type'] === 'replace_default_value') {
            Assert::keyExists($data, 'replace_map');
        }

        return new self(
            $data['class'],
            $data['method'],
            $data['position'],
            $data['type'],
            $data['default_value'] ?? null,
            $data['replace_map'] ?? []
        );
    }

    public function getClass(): string
    {
        return $this->class;
    }

    public function getMethod(): string
    {
        return $this->method;
    }

    public function getPosition(): int
    {
        return $this->position;
    }

    public function getType(): string
    {
        return $this->type;
    }

    /**
     * @return mixed|null
     */
    public function getDefaultValue()
    {
        return $this->defaultValue;
    }

    /**
     * @return string[]
     */
    public function getReplaceMap(): array
    {
        return $this->replaceMap;
    }
}
