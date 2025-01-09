<?php

namespace Rector\Tests\DeadCode\Rector\ClassMethod\RemoveUselessOverrideAttributeRector\Fixture;

interface ExtendsAndImplementInterface
{
    public function foo(): void;
}

abstract class ExtendsAndImplementContract
{
    public function bar(): void
    {
        echo 'self::bar';
    }
}

final class ExtendsAndImplement extends ExtendsAndImplementContract implements ExtendsAndImplementInterface
{
    #[\Override]
    public function foo(): void
    {
        echo 'foo';
    }

    #[\Override]
    public function bar(): void
    {
        echo 'bar';
    }

    #[\Override]
    public function baz(): void
    {
        echo 'bar';
    }
}
?>
-----
<?php

namespace Rector\Tests\DeadCode\Rector\ClassMethod\RemoveUselessOverrideAttributeRector\Fixture;

interface ExtendsAndImplementInterface
{
    public function foo(): void;
}

abstract class ExtendsAndImplementContract
{
    public function bar(): void
    {
        echo 'self::bar';
    }
}

final class ExtendsAndImplement extends ExtendsAndImplementContract implements ExtendsAndImplementInterface
{
    #[\Override]
    public function foo(): void
    {
        echo 'foo';
    }

    #[\Override]
    public function bar(): void
    {
        echo 'bar';
    }

    public function baz(): void
    {
        echo 'bar';
    }
}
?>
